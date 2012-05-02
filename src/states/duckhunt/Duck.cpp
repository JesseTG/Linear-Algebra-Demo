#include "../../../include/states/duckhunt/Duck.h"

#include <iostream>


const int DUCK_SCALE = 2;

float Duck::speed = 3;
std::unordered_map<DuckFrame, RectInt> Duck::frames;

Duck::Duck()
{
    frame = 0;
    frames[DuckFrame::UP_1] = RectInt(0, 197, 29, 229);
    frames[DuckFrame::UP_2] = RectInt(35, 197, 64, 229);
    frames[DuckFrame::UP_3] = RectInt(67, 197, 96, 229);
    frames[DuckFrame::NORM_1] = RectInt(98, 198, 132, 229);
    frames[DuckFrame::NORM_2] = RectInt(136, 199, 170, 230);
    frames[DuckFrame::NORM_3] = RectInt(173, 198, 206, 229);

    initSprite(sprite, sprites, frames[DuckFrame::UP_1], DUCK_SCALE);
    setSpriteBuffer(sprite, buffer);



    updateShotBox();

    sprite.SetPosition(Random::Random(0, 640), Random::Random(0, 240));
    setRandomDirection();
    probChangeVel = .0085;
}

Duck::~Duck()
{
    //dtor
}

void Duck::fly()
{
    if (Random::Random(0.0f, 1.0f) <= probChangeVel) setRandomDirection();


    sprite.Move(velocity);

    if (sprite.GetPosition().x < buffer[LEFT]) {
        sprite.SetX(buffer[LEFT]);
        velocity.x *= -1;
    }
    if (sprite.GetPosition().x > buffer[RIGHT]) {
        sprite.SetX(buffer[RIGHT]);
        velocity.x *= -1;
    }
    if (sprite.GetPosition().y < buffer[UP]) {
        sprite.SetY(buffer[UP]);
        velocity.y *= -1;
    }
    if (sprite.GetPosition().y > 3*Window.GetHeight()/5) {
        sprite.SetY(3*Window.GetHeight()/5);
        velocity.y *= -1;
    }

    updateShotBox();

}

void Duck::flyAway()
{

}

void Duck::die()
{
    std::cout << "BANG!\n";
}

void Duck::updateShotBox()
{
    shotbox.Left   = sprite.TransformToGlobal(VectorFloat(0, 0)).x;
    shotbox.Right  = sprite.GetPosition().x + sprite.GetSize().x/2;
    shotbox.Top    = sprite.TransformToGlobal(VectorFloat(0, 0)).y;
    shotbox.Bottom = sprite.GetPosition().y + sprite.GetSize().y/2;
}

void Duck::updateAnimation()
{
    sprite.FlipX(velocity.x < 0);  //If the duck is flying left, flip its sprite

    //This expression uses a sine wave to animate the duck
    sprite.SetSubRect(frames[DuckFrame(lround(sin(25*animationtimer.GetElapsedTime()-.5)+1))]);
}

void Duck::setRandomDirection()
{
    float angle = Random::Random(0.0f, 360.0f);

    velocity = VectorFloat(speed * sin(angle), speed * cos(angle));
}
