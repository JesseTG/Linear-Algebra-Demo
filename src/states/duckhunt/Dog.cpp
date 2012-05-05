#include "../../../include/states/duckhunt/Dog.h"

const int DOG_SCALE = 2;

Dog::Dog()
{
    frame = 0;
    frames[DogFrame::SNIFF_1] = RectInt(  3, 233,  56, 275);
    frames[DogFrame::SNIFF_2] = RectInt( 59, 233, 114, 275);
    frames[DogFrame::WALK_1 ] = RectInt(119, 233, 170, 275);
    frames[DogFrame::WALK_2 ] = RectInt(173, 233, 226, 275);
    frames[DogFrame::WALK_3 ] = RectInt(230, 233, 282, 275);

    initSprite(sprite, sprites, frames[DogFrame::SNIFF_1], DOG_SCALE,
               VectorFloat(Window.GetWidth()*.1, Window.GetHeight()*.70));

    state = DogState::WALKING;
}

Dog::~Dog()
{
    //dtor
}

void Dog::walk()
{
}

void Dog::animate()
{
    if (state == DogState::WALKING) {
        sprite.SetSubRect(frames[DogFrame((int(5*animationtimer.GetElapsedTime())%3)+2)]);
    }
}
