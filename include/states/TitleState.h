#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "../Declarations.h"
#include "../State.h"

/*
 * This is my project's title screen.  It features only a rotating cross and
 * some information off to the sides.
 */

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

    sf::Image bgimage;
    sf::Sprite bg;

    RectFloat mariobox;
};

TitleState::TitleState()
{
    //NADA means next frame we stay in this state, or we'd never see this one!
    setNextState(StateName::NADA);

    marioimage.LoadFromFile("./gfx/mario.png");
    marioimage.SetSmooth(false);

    mario.SetImage(marioimage);

    mario.SetScale(6, 6);
    mario.SetPosition(320, 240);
    mario.SetCenter(marioimage.GetWidth()/2.0, marioimage.GetHeight()/2.0);

    bgimage.LoadFromFile("./gfx/bgtile.png");
    bg.SetImage(bgimage);

    Window.Clear();

    for (int i = 0; i < Window.GetWidth(); i += bgimage.GetWidth()) {
        for (int j = 0; j < Window.GetHeight(); j += bgimage.GetHeight()) {
            bg.SetPosition(i, j);
            Window.Draw(bg);
        }
    }
}

TitleState::~TitleState()
{

}

void TitleState::input()
{
    //TODO: Work on getting input!  Need to get familiar IRrecv's API again.
    if (/* user presses a certain button */true == false)
    setNextState(/* state 2*/StateName::TITLE);
}

void TitleState::logic()
{
    mario.Rotate(1);
    VectorFloat temp = mario.TransformToGlobal(VectorFloat(0, 0));
    VectorFloat temp2(mario.TransformToGlobal(VectorFloat(temp.x + marioimage.GetWidth()*mario.GetScale().x,
                                              temp.y + marioimage.GetHeight()*mario.GetScale().y)));
    mariobox.Top = temp.y;
    mariobox.Left = temp.x;
    mariobox.Bottom = temp2.y;
    mariobox.Right = temp2.x;
}

void TitleState::render()
{
    for (int i = 0; i < Window.GetWidth(); i += bgimage.GetWidth()) {
        for (int j = 0; j < Window.GetHeight(); j += bgimage.GetHeight()) {
            bg.SetPosition(i, j);
            if (mariobox.Contains(bg.GetPosition().x, bg.GetPosition().y))
                Window.Draw(bg);
        }
    }


    Window.Draw(mario);
    Window.Display();
}

#endif //TITLESTATE_H
