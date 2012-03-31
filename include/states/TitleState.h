#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "../Declarations.h"
#include "../State.h"

/*
 * This is my project's title screen.  It features only a rotating sprite
 * some information off to the sides.
 */

const float ROTATION = .5;  //The angle the sprite spins each frame.

class TitleState : public State
{
  public:
    TitleState();
    ~TitleState();

    void input();
    void logic();
    void render();

  private:
    sf::Image marioimage;
    sf::Sprite mario;



    sf::String title;
};

TitleState::TitleState()
{
    logger.log("Entering Title state.");

    //NADA means next frame we stay in this state, or we'd never see this one!
    setNextState(StateName::NADA);


    if (marioimage.LoadFromFile("./gfx/mario.png"))
        logger.log("Loaded title screen sprite.");
    marioimage.SetSmooth(false);

    mario.SetImage(marioimage);
    mario.SetScale(6, 6);
    mario.SetPosition(320, 240);
    mario.SetCenter(marioimage.GetWidth()/2.0, marioimage.GetHeight()/2.0);

    title.SetFont(font);
    title.SetSize(24);
    title.SetText("Linear Algebra Demo\n\n"
                  "Jesse Talavera-Greenberg\n\n"
                  "O/P: Previous/Next Screen");

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

void TitleState::render()
{
    Window.Draw(bg);  //Puts the background on the screen.
    Window.Draw(title);  //Puts the title on the screen.
    Window.Draw(mario);  //Puts the Mario sprite on the screen.
    Window.Display();  //Now actually displays the screen.
}

#endif //TITLESTATE_H
