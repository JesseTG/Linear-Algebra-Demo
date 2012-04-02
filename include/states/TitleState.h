#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "../Declarations.h"
#include "../State.h"

/*
 * This is my project's title screen.  It features only a rotating sprite and
 * some information off to the sides.
 */

//These are here so we avoid "magic numbers"; aka numbers that don't appear at
//first glance to hold any significance.  Very bad in software development,
//especially if this magic number is reused.
const float ROTATION = .5;  //The angle the sprite spins each frame.
const int MARIO_SCALE = 10;  //The factor we scale the sprite by.
const int FONT_SIZE = 24;  //Size of the font, not the sf::Strings using it.

/*
 * This is a class, aka a blueprint for a type of data.  It's a sort of black box
 * that abstracts away certain processes so we can describe solutions in terms of
 */
class TitleState : public State
{
  public:
    TitleState();
    ~TitleState();

    void input();
    void logic();
    void render() const;

  private:
    Sprite mario;
    sf::String title;
};

TitleState::TitleState()
{
    logger.log("Entering Title state.");

    //NADA means next frame we stay in this state, or we'd never see this one!
    setNextState(StateName::NADA);

    //Sets up Mario's sprite  //////////////////////////////////////////////////
    mario.SetImage(sprites);
    mario.SetSubRect(RectInt(0, 0, 16, 16));
    mario.SetCenter(mario.GetSubRect().GetWidth()/2,
                    mario.GetSubRect().GetHeight()/2);
    mario.SetScale(MARIO_SCALE, MARIO_SCALE);
    mario.SetPosition(center.x, Window.GetHeight()/1.5);

    ////////////////////////////////////////////////////////////////////////////

    //Sets up the title text  //////////////////////////////////////////////////
    title.SetPosition(8, 8);
    title.SetSize(FONT_SIZE);
    title.SetText("Linear Algebra Demo\n\n"
                  "Jesse Talavera-Greenberg\n\n"
                  "O/P: Previous/Next Screen");
    ////////////////////////////////////////////////////////////////////////////

    Window.Clear();
}

TitleState::~TitleState()
{
    logger.log("Exiting Title state.");
}

void TitleState::input()
{
    while (Window.GetEvent(event))
        if (event.Type == sf::Event::KeyPressed &&
            event.Key.Code == sf::Key::P)
                setNextState(StateName::VECTORS);
}

void TitleState::logic()
{
    mario.Rotate(ROTATION);
}

void TitleState::render() const
{
    Window.Draw(bg);  //Puts the background on the screen.
    Window.Draw(title);  //Puts the title on the screen.
    Window.Draw(mario);  //Puts the Mario sprite on the screen.
    Window.Display();  //Now actually displays the screen.
}

/*
   I really do think you should learn to code, Mr. Ski, as a math teacher
   there's so much you could do after spending a summer learning how to use
   Octave or Maxima (both of which are free).
 */

#endif //TITLESTATE_H
