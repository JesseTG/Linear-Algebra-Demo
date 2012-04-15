#include "../include/states/TitleState.h"

//These are here so we avoid "magic numbers"; aka numbers that don't appear at
//first glance to hold any significance.  Very bad in software development,
//especially if this magic number is reused.
const float ROTATION = .5;  //The angle the sprite spins each frame.
const int MARIO_SCALE = 10;  //The factor we scale the sprite by.

TitleState::TitleState()
{
    logger.log("Entering Title state.");

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
    checkForNextState(StateName::NADA, StateName::VECTORS);
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
