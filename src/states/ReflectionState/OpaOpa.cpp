#include "../../../include/states/ReflectionState/OpaOpa.h"

const int OPAOPA_SCALE = 5;
const int OPAOPA_SPEED = 5;

OpaOpa::OpaOpa()
{
    initSprite(ship, sprites, RectInt(58, 19, 74, 30), OPAOPA_SCALE);
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
