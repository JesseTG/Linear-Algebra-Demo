#include "../../../include/states/duckhunt/Duck.h"

#include <iostream>


const int DUCK_SCALE = 2;

float Duck::speed = 3;
std::unordered_map<DuckFrame, RectInt> Duck::frames;

Duck::Duck()
{
    frame = 0;
    frames[DuckFrame::UP_1   ] = RectInt(  0, 197,  29, 229);
    frames[DuckFrame::UP_2   ] = RectInt( 35, 197,  64, 229);
    frames[DuckFrame::UP_3   ] = RectInt( 67, 197,  96, 229);
    frames[DuckFrame::NORM_1 ] = RectInt( 98, 198, 132, 229);
    frames[DuckFrame::NORM_2 ] = RectInt(136, 199, 170, 230);
    frames[DuckFrame::NORM_3 ] = RectInt(173, 198, 206, 229);
    frames[DuckFrame::SHOT   ] = RectInt(212, 202, 243, 231);
    frames[DuckFrame::FALLING] = RectInt(245, 201, 263, 232);

    initSprite(sprite, sprites, frames[DuckFrame::NORM_1], DUCK_SCALE);
    setSpriteBuffer(sprite, buffer);

    is_alive = true;
    is_hit_ground = false;

    updateShotBox();

    sprite.SetPosition(Random::Random(0, 640), Random::Random(0, 240));
    setRandomDirection();
    probChangeVel = .0085;
}

Duck::~Duck()
{
    //dtor
}

void Duck::move()
{
    if (is_alive) fly();
    else if (!is_hit_ground) fall();

    updateShotBox();

}

void Duck::flyAway()
{

}

void Duck::die()
{
    if (is_alive) {
        is_alive = false;
        sprite.SetSubRect(frames[DuckFrame::SHOT]);
        velocity = VectorFloat(0, 3);
        actiontimer.Reset();
        animationtimer.Reset();
    }
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

    if (is_alive) {
        //This expression uses a sine wave to animate the duck
        sprite.SetSubRect(frames[DuckFrame(lround(sin(25*animationtimer.GetElapsedTime()-.5)+1))]);
    }

}

void Duck::setRandomDirection()
{
    float angle = Random::Random(0.0f, 360.0f);

    velocity = VectorFloat(speed * sin(angle), speed * cos(angle));
}

void Duck::fly()
{
    if (Random::Random(0.0f, 1.0f) <= probChangeVel) setRandomDirection();


    sprite.Move(velocity);

    if (!IN_RANGE(sprite.GetPosition().x, buffer[LEFT], buffer[RIGHT])) {
        if (sprite.GetPosition().x < buffer[LEFT]) sprite.SetX(buffer[LEFT]);
        else sprite.SetX(buffer[RIGHT]);
        velocity.x *= -1;
    }

    float temp = 3*Window.GetHeight()/5;
    if (!IN_RANGE(sprite.GetPosition().y, buffer[UP], temp)) {
        if (sprite.GetPosition().y < temp) sprite.SetY(buffer[UP]);
        else sprite.SetY(temp);
        velocity.y *= -1;
    }
}

void Duck::fall()
{
    if (actiontimer.GetElapsedTime() < 1 && sprite.GetPosition().y >= Window.GetHeight()*.8) {
        is_hit_ground = true;
        return;
    }

    if (actiontimer.GetElapsedTime() >= 1) {
        if (sprite.GetSubRect().GetHeight() != frames[DuckFrame::FALLING].GetHeight())
            sprite.SetSubRect(frames[DuckFrame::FALLING]);

        sprite.Move(velocity);
        int temp = floor(sin(10*animationtimer.GetElapsedTime()))+1;
        sprite.FlipX(temp);
        //TODO: Fix bug; ducks will FlipY() but not FlipX()
    }
}
