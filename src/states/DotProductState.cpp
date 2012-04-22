#include <cmath>

#include "../../include/states/DotProductState.h"

#define _USE_MATH_DEFINES
#define PI M_PI

const int BLUE_FALCON_SCALE = 2;
const int BLUE_FALCON_SPEED = 8;

//This function is taken from the libraries for the Arduino microcontroller.
float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

DotProductState::DotProductState()
{
    //The Blue Falcon spritesheet is big enough to justify a new image file  ///
    bfsprites.LoadFromFile("./gfx/bluefalcon.png");
    bfsprites.SetSmooth(false);
    ////////////////////////////////////////////////////////////////////////////

    //Puts all the frames into this array  /////////////////////////////////////
    //Order's weird due to the ordering of the sprites  ////////////////////////
    frames[19] = RectInt(0, 0, 49, 43);
    frames[20] = RectInt(55, 0, 106, 42);
    frames[21] = RectInt(114, 0, 167, 42);
    frames[22] = RectInt(175, 0, 229, 42);
    frames[23] = RectInt(237, 2, 293, 42);
    frames[24] = RectInt(301, 4, 363, 42);
    frames[25] = RectInt(371, 4, 435, 42);
    frames[26] = RectInt(443, 6, 507, 42);
    frames[27] = RectInt(515, 5, 579, 42);
    frames[28] = RectInt(587, 1, 649, 42);
    frames[29] = RectInt(656, 0, 711, 45);
    frames[30] = RectInt(713, 0, 758, 46);
    frames[31] = RectInt(766, 0, 806, 46);
    frames[0] = RectInt(814, 0, 852, 46);
    frames[1] = RectInt(860, 0, 900, 46);
    frames[2] = RectInt(903, 0, 948, 46);
    frames[3] = RectInt(0, 43, 55, 88);
    frames[4] = RectInt(61, 43, 122, 84);
    frames[5] = RectInt(130, 47, 194, 84);
    frames[6] = RectInt(202, 48, 266, 84);
    frames[7] = RectInt(274, 46, 338, 84);
    frames[8] = RectInt(346, 46, 408, 84);
    frames[9] = RectInt(416, 44, 472, 84);
    frames[10] = RectInt(480, 42, 534, 84);
    frames[11] = RectInt(542, 42, 595, 83);
    frames[12] = RectInt(604, 42, 656, 84);
    frames[13] = RectInt(665, 45, 713, 88);
    frames[14] = RectInt(715, 46, 767, 88);
    frames[15] = RectInt(775, 48, 831, 88);
    frames[16] = RectInt(839, 50, 897, 87);
    frames[17] = RectInt(900, 46, 955, 85);
    frames[18] = RectInt(0, 88, 50, 129);
    ////////////////////////////////////////////////////////////////////////////

    //Prepares the actual sprite for on-screen display  ////////////////////////
    initSprite(bluefalcon, bfsprites, frames[0], BLUE_FALCON_SCALE);
    setSpriteBuffer(bluefalcon, buffer);
    ////////////////////////////////////////////////////////////////////////////
}

void DotProductState::input()
{
    checkForNextState(StateName::TRANSLATION_DISTANCE_LENGTH, StateName::REFLECTION);

    ismoving[UP] = INPUT.IsKeyDown(sf::Key::Up);
    ismoving[DOWN] = INPUT.IsKeyDown(sf::Key::Down);
    ismoving[LEFT] = INPUT.IsKeyDown(sf::Key::Left);
    ismoving[RIGHT] = INPUT.IsKeyDown(sf::Key::Right);
}

void DotProductState::logic()
{
    inputmove(BLUE_FALCON_SPEED, ismoving, bluefalcon, buffer);

    VectorFloat temp = bluefalcon.GetPosition() -
                       VectorFloat(INPUT.GetMouseX(),
                                   INPUT.GetMouseY());

    float angletomouse = atan2(temp.x, temp.y) * (180/PI);
    angletomouse = map(angletomouse, -180, 180, 0, 360);

    bluefalcon.SetSubRect(frames[round(map(angletomouse, 360, 0, 0, frames.size()-1))]);
    bluefalcon.SetCenter(bluefalcon.GetSubRect().GetWidth()/2,
                         bluefalcon.GetSubRect().GetHeight()/2);

    setSpriteBuffer(bluefalcon, buffer);

    stats_to_string.str("");
    stats_to_string << "Dot Products" <<
                       "\n\nAngle: " << angletomouse << " degrees" <<
                       "\n\nArrow Keys: Movement" <<
                       "\nMouse: Rotate Vehicle";
    stats.SetText(stats_to_string.str());

}

void DotProductState::render() const
{
    Window.Draw(bg);
    Window.Draw(bluefalcon);
    Window.Draw(stats);
    Window.Display();
}
