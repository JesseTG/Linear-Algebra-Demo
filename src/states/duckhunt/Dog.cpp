#include "../../../include/states/duckhunt/Dog.h"

const int DOG_SCALE = 2;

Dog::Dog()
{
    frames[DogFrame::SNIFF_1] = RectInt(3, 235, 56, 275);
    frames[DogFrame::SNIFF_2] = RectInt(59, 235, 114, 275);

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

    }
}
