#include <cmath>

#include "../include/states/DotProductState.h"

#define _USE_MATH_DEFINES
#define PI M_PI

const int BLUE_FALCON_SCALE = 2;
const int BLUE_FALCON_SPEED = 8;

float magnitude(const VectorFloat& v)
{ return hypot(v.x, v.y); }

VectorFloat normalize(const VectorFloat& v)
{ return VectorFloat(v.x/magnitude(v), v.y/magnitude(v)); }

float dotProduct(const VectorFloat& a, const VectorFloat& b)
{
    VectorFloat c = normalize(a);
    VectorFloat d = normalize(b);
    return c.x*d.x+c.y*d.y;
}

float getAngleBetween(const VectorFloat& a, const VectorFloat& b)
{ return dotProduct(a, b)/(magnitude(a)*magnitude(b)); }

//This function is taken from the libraries for the Arduino microcontroller.
float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

DotProductState::DotProductState()
{
    logger.log("Entering Dot Product state.");
    bfsprites.LoadFromFile("./gfx/bluefalcon.png");
    bfsprites.SetSmooth(false);


    //Puts all the frames into this array  /////////////////////////////////////
    frames[0] = RectInt(0, 0, 49, 43);
    frames[1] = RectInt(55, 0, 106, 42);
    frames[2] = RectInt(114, 0, 167, 42);
    frames[3] = RectInt(175, 0, 229, 42);
    frames[4] = RectInt(237, 2, 293, 42);
    frames[5] = RectInt(301, 4, 363, 42);
    frames[6] = RectInt(371, 4, 435, 42);
    frames[7] = RectInt(443, 6, 507, 42);
    frames[8] = RectInt(515, 5, 579, 42);
    frames[9] = RectInt(587, 1, 649, 42);
    frames[10] = RectInt(656, 0, 711, 45);
    frames[11] = RectInt(713, 0, 758, 46);
    frames[12] = RectInt(766, 0, 806, 46);
    frames[13] = RectInt(814, 0, 852, 46);
    frames[14] = RectInt(860, 0, 900, 46);
    frames[15] = RectInt(903, 0, 948, 46);
    ////////////////////////////////////////////////////////////////////////////

    bluefalcon.SetImage(bfsprites);
    bluefalcon.SetSubRect(frames[0]);
    bluefalcon.SetScale(BLUE_FALCON_SCALE, BLUE_FALCON_SCALE);
    bluefalcon.SetCenter(bluefalcon.GetSubRect().GetWidth()/2,
                         bluefalcon.GetSubRect().GetHeight()/2);
    bluefalcon.SetPosition(center);

    //TODO: Put all of the Falcon's frames into the unordered map
}

DotProductState::~DotProductState()
{
    logger.log("Exiting Dot Product state.");
}

void DotProductState::input()
{
    checkForNextState(StateName::TRANSLATION_DISTANCE_LENGTH, StateName::NADA);

    ismoving[UP] = Window.GetInput().IsKeyDown(sf::Key::Up);
    ismoving[DOWN] = Window.GetInput().IsKeyDown(sf::Key::Down);
    ismoving[LEFT] = Window.GetInput().IsKeyDown(sf::Key::Left);
    ismoving[RIGHT] = Window.GetInput().IsKeyDown(sf::Key::Right);
}

void DotProductState::logic()
{
    bluefalcon.Move(0, -BLUE_FALCON_SPEED * ismoving[UP] /* (bluefalcon.GetPosition().y > buffer[UP])*/);
    bluefalcon.Move(0, BLUE_FALCON_SPEED * ismoving[DOWN] /* (bluefalcon.GetPosition().y < buffer[DOWN])*/);
    bluefalcon.Move(-BLUE_FALCON_SPEED * ismoving[LEFT] /* (bluefalcon.GetPosition().x > buffer[LEFT])*/, 0);
    bluefalcon.Move(BLUE_FALCON_SPEED * ismoving[RIGHT] /* (bluefalcon.GetPosition().x < buffer[RIGHT])*/, 0);

    VectorFloat temp = bluefalcon.GetPosition() -
                       VectorFloat(Window.GetInput().GetMouseX(),
                                   Window.GetInput().GetMouseY());

    float angletomouse = atan2(temp.x, temp.y) * (180/PI);
    angletomouse = map(angletomouse, -180, 180, 0, 360);

    bluefalcon.SetSubRect(frames[map(angletomouse, 0, 360, 0, frames.size())]);

    stats_to_string.str("");
    stats_to_string << angletomouse;
    stats.SetText(stats_to_string.str());

}

void DotProductState::render() const
{
    Window.Draw(bg);
    Window.Draw(bluefalcon);
    Window.Draw(stats);
    Window.Display();
}
