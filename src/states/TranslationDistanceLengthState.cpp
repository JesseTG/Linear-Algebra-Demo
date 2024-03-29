#include "../../include/states/TranslationDistanceLengthState.h"

const int HERO_SCALE      = 6;
const int HERO_MOVE_SPEED = 2;
const int GHOST_SCALE     = 3;
const int FEAR_DISTANCE   = 100;  //The ghost must be this far away for the hero to move

TranslationDistanceLengthState::TranslationDistanceLengthState()
{
    //Preps the unordered map for easy sprite access
    heroframes[HeroFrame::NORTH_LEFT ] = RectInt(102,   0, 118,  16);
    heroframes[HeroFrame::NORTH_RIGHT] = RectInt(120,   0, 136,  16);
    heroframes[HeroFrame::SOUTH_LEFT ] = RectInt( 39,   0,  55,  16);
    heroframes[HeroFrame::SOUTH_RIGHT] = RectInt( 57,   0,  73,  16);
    heroframes[HeroFrame::WEST_LEFT  ] = RectInt( 88,   0, 100,  16);
    heroframes[HeroFrame::WEST_RIGHT ] = RectInt( 75,   0,  86,  16);
    heroframes[HeroFrame::EAST_RIGHT ] = RectInt(138,   0, 150,  16);
    heroframes[HeroFrame::EAST_LEFT  ] = RectInt(152,   0, 163,  16);

    //Preps the Hero sprite itself
    initSprite(hero, sprites, heroframes[HeroFrame::SOUTH_LEFT], HERO_SCALE);
    setSpriteBuffer(hero, buffer);
    frame = char(HeroFrame::SOUTH_LEFT);

    //Preps the Ghost sprite
    initSprite(ghost, sprites, RectInt(34, 18, 58, 48), GHOST_SCALE, MOUSE);

    //Hides the mouse cursor on this screen
    Window.ShowMouseCursor(false);
}

TranslationDistanceLengthState::~TranslationDistanceLengthState()
{
    //Shows the mouse cursor as we leave this screen
    Window.ShowMouseCursor(true);
}

void TranslationDistanceLengthState::input()
{
    checkForNextState(StateName::MATRICES, StateName::DOT_PRODUCTS);

    //Ensures that the hero moves ONLY horizontally and vertically
    bool movinghorizontal = !ismoving[LEFT] * !ismoving[RIGHT];
    ismoving[UP   ]       = INPUT.IsKeyDown(sf::Key::Up  ) * movinghorizontal;
    ismoving[DOWN ]       = INPUT.IsKeyDown(sf::Key::Down) * movinghorizontal;
    bool movingvertical   = !ismoving[UP] * !ismoving[DOWN];
    ismoving[LEFT ]       = INPUT.IsKeyDown(sf::Key::Left ) * movingvertical;
    ismoving[RIGHT]       = INPUT.IsKeyDown(sf::Key::Right) * movingvertical;
}

void TranslationDistanceLengthState::logic()
{
    float distance = MAGNITUDE(hero.GetPosition() - ghost.GetPosition());  //Distance between hero and ghost
    if (distance > FEAR_DISTANCE) {  //If the ghost is close to the hero...
        if (hero.GetColor() != Color::White) hero.SetColor(Color::White);  //Remove his color if not already
        inputmove(HERO_MOVE_SPEED, ismoving, hero, buffer);  //And move him
    }
    else {
        hero.SetColor(Color::Blue);  //Blue == terrified and frozen!
    }


    //Changes the Hero's sprite direction, but does NOT interfere with animation rate
    if (ismoving[UP] && frame != 0 && frame != 1)
        hero.SetSubRect(heroframes[HeroFrame(frame = 0)]);
    else if (ismoving[DOWN] && frame != 2 && frame != 3)
        hero.SetSubRect(heroframes[HeroFrame(frame = 2)]);
    else if (ismoving[LEFT] && frame != 6 && frame != 7)
        hero.SetSubRect(heroframes[HeroFrame(frame = 6)]);
    else if (ismoving[RIGHT] && frame != 4 && frame != 5)
        hero.SetSubRect(heroframes[HeroFrame(frame = 4)]);

    if (animationtimer.GetElapsedTime() >= 1) {  //Keeps the animation at JUST the right speed
        for (const bool& i : ismoving) if (i) break;  //Don't change the frame if moving
        frame += (frame % 2 == 0) ? 1 : -1;  //Abuse the properties of boolean logic (true == 1, false == 0)
        hero.SetSubRect(heroframes[HeroFrame(frame)]);
        animationtimer.Reset();
    }

    //The Ghost follows the mouse
    ghost.SetPosition(MOUSE);

    //Prepare text for output
    stats_to_text.str("");
    stats_to_text << "Translation, Distance, and Length\n\n"
                  << "Distance Between Ghost and Hero: " << std::setprecision(3) << distance
                  << "\n\nArrow Keys: Move Hero\n"
                  << "Mouse: Move Ghost\n\n"
                  << (hero.GetColor() == Color::Blue ? "\"Oh s**t!\"" : "") << "\n\n"
                  << "GFX: Dragon Warrior (Enix, 1989)";
    stats.SetText(stats_to_text.str());
}

void TranslationDistanceLengthState::render()
{
    Window.Draw(bg   );
    Window.Draw(hero );
    Window.Draw(ghost);
    Window.Draw(stats);
    Window.Display();
}
