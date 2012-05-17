#include "../../include/states/TitleState.h"

//These are here so we avoid "magic numbers"; aka numbers that don't appear at
//first glance to hold any significance.  Very bad in software development,
//especially if this magic number is reused.
const float MARIO_ROTATION = .5;  //The angle the sprite spins each frame.
const int   MARIO_SCALE    = 10;  //The factor we scale the sprite by.

TitleState::TitleState()
{
    //Sets up Mario's sprite  //////////////////////////////////////////////////
    initSprite(mario, sprites, RectInt(0, 0, 16, 16), MARIO_SCALE,
               VectorFloat(CENTER.x, SCREEN.GetHeight()/1.5));
    ////////////////////////////////////////////////////////////////////////////

    //Sets up the title text  //////////////////////////////////////////////////
    title.SetText("Linear Algebra Demo       \n\n"
                  "Jesse Talavera-Greenberg  \n\n"
                  "O/P: Previous/Next Screen   \n"
                  "F4: Toggle Fullscreen     \n\n"
                  "GFX: Super Mario Bros. (Nintendo, 1985)"
                  );
    ////////////////////////////////////////////////////////////////////////////
}

void TitleState::input()
{
    checkForNextState(StateName::NADA, StateName::VECTORS);
}

void TitleState::logic()
{
    mario.Rotate(MARIO_ROTATION);
}

void TitleState::render()
{
    Window.Draw(bg   );  //Puts the background on the screen.
    Window.Draw(mario);  //Puts the Mario sprite on the screen.
    Window.Draw(title);  //Puts the title on the screen.
    Window.Display();  //Now actually displays the screen.
}
