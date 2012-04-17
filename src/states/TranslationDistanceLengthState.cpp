#include "../../include/states/TranslationDistanceLengthState.h"

const int HERO_SCALE = 6;
const int HERO_MOVE_SPEED = 2;
const int GHOST_SCALE = 3;

TranslationDistanceLengthState::TranslationDistanceLengthState()
{
    logger.log("Entering Translation, Distance, Length state");

    //Preps the unordered map for easy sprite access  //////////////////////////
    heroframes.insert(HeroPair(HeroFrame::NORTH_LEFT, RectInt(102, 0, 118, 16)));
    heroframes.insert(HeroPair(HeroFrame::NORTH_RIGHT, RectInt(120, 0, 136, 16)));
    heroframes.insert(HeroPair(HeroFrame::SOUTH_LEFT, RectInt(39, 0, 55, 16)));
    heroframes.insert(HeroPair(HeroFrame::SOUTH_RIGHT, RectInt(57, 0, 73, 16)));
    heroframes.insert(HeroPair(HeroFrame::WEST_LEFT, RectInt(88, 0, 100, 16)));
    heroframes.insert(HeroPair(HeroFrame::WEST_RIGHT, RectInt(75, 0, 86, 16)));
    heroframes.insert(HeroPair(HeroFrame::EAST_RIGHT, RectInt(138, 0, 150, 16)));
    heroframes.insert(HeroPair(HeroFrame::EAST_LEFT, RectInt(152, 0, 163, 16)));
    ////////////////////////////////////////////////////////////////////////////

    //Preps the Hero sprite itself  ////////////////////////////////////////////
    hero.SetImage(sprites);
    hero.SetSubRect(heroframes[HeroFrame::SOUTH_LEFT]);
    hero.SetCenter(hero.GetSubRect().GetWidth()/2,
                   hero.GetSubRect().GetHeight()/2);
    hero.SetScale(HERO_SCALE, HERO_SCALE);
    hero.SetPosition(center);
    frame = char(HeroFrame::SOUTH_LEFT);

    setSpriteBuffer(hero, buffer);
    ////////////////////////////////////////////////////////////////////////////

    //Preps the Ghost sprite  //////////////////////////////////////////////////
    ghost.SetImage(sprites);
    ghost.SetSubRect(RectInt(34, 18, 58, 48));
    ghost.SetCenter(ghost.GetSubRect().GetWidth()/2,
                    ghost.GetSubRect().GetHeight()/2);
    ghost.SetScale(GHOST_SCALE, GHOST_SCALE);
    ghost.SetPosition(INPUT.GetMouseX(),
                      INPUT.GetMouseY());
    ////////////////////////////////////////////////////////////////////////////
}

TranslationDistanceLengthState::~TranslationDistanceLengthState()
{
    logger.log("Exiting Translation, Distance, Length state.");
}

void TranslationDistanceLengthState::input()
{
    checkForNextState(StateName::MATRICES, StateName::DOT_PRODUCTS);

    bool movinghorizontal = !ismoving[LEFT] * !ismoving[RIGHT];
    ismoving[UP] = INPUT.IsKeyDown(sf::Key::Up) * movinghorizontal;
    ismoving[DOWN] = INPUT.IsKeyDown(sf::Key::Down) * movinghorizontal;
    bool movingvertical = !ismoving[UP] * !ismoving[DOWN];
    ismoving[LEFT] = INPUT.IsKeyDown(sf::Key::Left) * movingvertical;
    ismoving[RIGHT] = INPUT.IsKeyDown(sf::Key::Right) * movingvertical;
}

void TranslationDistanceLengthState::logic()
{
    //Prevents the Hero from moving diagonally, as in Dragon Quest, but stops  /
    //him if the Ghost is too close.  //////////////////////////////////////////
    VectorFloat distancevector = hero.GetPosition() - ghost.GetPosition();
    float distance = hypot(distancevector.x, distancevector.y);
    if (distance > 100) {
        if (hero.GetColor() != Color::White) hero.SetColor(Color::White);
        inputmove(HERO_MOVE_SPEED, ismoving, hero, buffer);
    }
    else {
        hero.SetColor(Color::Blue);  //Blue == terrified!
    }
    ////////////////////////////////////////////////////////////////////////////

    //Changes the Hero's sprite direction, but does NOT interfere with animation
    if (ismoving[UP] && frame != 0 && frame != 1)
        hero.SetSubRect(heroframes[HeroFrame(frame = 0)]);
    else if (ismoving[DOWN] && frame != 2 && frame != 3)
        hero.SetSubRect(heroframes[HeroFrame(frame = 2)]);
    else if (ismoving[LEFT] && frame != 6 && frame != 7)
        hero.SetSubRect(heroframes[HeroFrame(frame = 6)]);
    else if (ismoving[RIGHT] && frame != 4 && frame != 5)
        hero.SetSubRect(heroframes[HeroFrame(frame = 4)]);
    ////////////////////////////////////////////////////////////////////////////

    //Keeps the animation at JUST the right speed  /////////////////////////////
    if (int(animationtimer.GetElapsedTime()) == 1) {
        for (bool& i : ismoving) if (i) break;  //Don't change the frame if moving
        if (frame % 2 == 0) frame += 1; else frame -= 1;
        animationtimer.Reset();
        hero.SetSubRect(heroframes[HeroFrame(frame)]);
    }
    ////////////////////////////////////////////////////////////////////////////

    //The Ghost follows the mouse
    ghost.SetPosition(INPUT.GetMouseX(), INPUT.GetMouseY());

    stats_to_text.str("");
    stats_to_text << "Translation, Distance, and Length\n\n"
                  << "Distance Between Ghost and Hero: " << distance
                  << "\n\nArrow Keys: Move Hero\n"
                  << "Mouse: Move Ghost\n\n"
                  << (hero.GetColor() == Color::Blue ? "\"Oh s**t!\"" : "");
    stats.SetText(stats_to_text.str());
}

void TranslationDistanceLengthState::render() const
{
    Window.Draw(bg);
    Window.Draw(hero);
    Window.Draw(ghost);
    Window.Draw(stats);
    Window.Display();
}