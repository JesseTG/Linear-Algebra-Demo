#include "../../../include/states/ReflectionState/OpaOpa.h"

const int OPAOPA_SCALE = 5;
const int OPAOPA_SPEED = 5;

OpaOpa::OpaOpa()
{
    frames[0] = RectInt(58, 19, 74, 30);
    frames[1] = RectInt(74, 19, 90, 30);
    frames[2] = RectInt(90, 19, 106, 33);
    frames[3] = RectInt(106, 18, 122, 33);
    initSprite(ship, sprites, frames[currentframe = 0], OPAOPA_SCALE);
    setSpriteBuffer(getSprite(), buffer);
}

OpaOpa::~OpaOpa()
{
    //dtor
}

void OpaOpa::move()
{
    ismoving[UP] = INPUT.IsKeyDown(sf::Key::Up);
    ismoving[DOWN] = INPUT.IsKeyDown(sf::Key::Down);
    ismoving[LEFT] = INPUT.IsKeyDown(sf::Key::Left);
    ismoving[RIGHT] = INPUT.IsKeyDown(sf::Key::Right);
    inputmove(OPAOPA_SPEED, ismoving, getSprite(), buffer);
}

void OpaOpa::animate()
{
    if (ismoving[RIGHT]) ship.FlipX(false);
    else if (ismoving[LEFT]) ship.FlipX(true);

    if (ship.GetPosition().y <= (Window.GetHeight() - ship.GetSize().y)) {
        if (currentframe < 2) currentframe = 2;
    }
        else if (currentframe > 2) currentframe = 0;

    currentframe = EVEN(currentframe) ? ++currentframe : --currentframe;

    if (int(animationtimer.GetElapsedTime()*1000) >= 250) {
        ship.SetSubRect(frames[currentframe]);
        animationtimer.Reset();
    }
}
