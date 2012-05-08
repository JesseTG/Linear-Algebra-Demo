#include "../../../include/states/duckhunt/Dog.h"

const int DOG_SCALE = 2;
const float FACTOR = 2;

#include <iostream>

Dog::Dog()
{
    frame = 0;
    frames[DogFrame::SNIFF_1  ] = RectInt(  3, 233,  56, 275);
    frames[DogFrame::SNIFF_2  ] = RectInt( 59, 233, 114, 275);
    frames[DogFrame::WALK_1   ] = RectInt(119, 233, 170, 275);
    frames[DogFrame::WALK_2   ] = RectInt(173, 233, 226, 275);
    frames[DogFrame::WALK_3   ] = RectInt(230, 233, 282, 275);
    frames[DogFrame::EXCITED  ] = RectInt(  2, 280,  55, 328);
    frames[DogFrame::JUMP_UP  ] = RectInt( 62, 276,  97, 322);
    frames[DogFrame::JUMP_DOWN] = RectInt(104, 290, 137, 322);

    initSprite(sprite, sprites, frames[DogFrame::SNIFF_1], DOG_SCALE,
               VectorFloat(Window.GetWidth()*.1, Window.GetHeight()*.70));

    state = DogState::WALKING;
}

Dog::~Dog()
{
    //dtor
}

void Dog::act()
{
    switch (state) {
        case DogState::IDLE         : break;
        case DogState::WALKING      : walk();  break;
        case DogState::JUMPING_UP   :
        case DogState::JUMPING_DOWN : jump();  break;
        case DogState::HOLDING_1DUCK: rise(1); break;
        case DogState::HOLDING_2DUCK: rise(2); break;
        case DogState::LAUGHING     : rise(0); break;
        default: throw std::invalid_argument("Dog state #" + boost::lexical_cast<std::string, int>(int(state)) + " not recognized!");
    }

    prevstate = state;
}

void Dog::walk()
{
    sprite.Move(5.0/7.0, 0);
}

void Dog::jump()
{
    if (actiontimer.GetElapsedTime() <= 1 && state == DogState::JUMPING_UP) {
        sprite.SetSubRect(frames[DogFrame::EXCITED]);
    }
    else if (actiontimer.GetElapsedTime() <= FACTOR + 1) {
        float temp = 2*(2*(actiontimer.GetElapsedTime()-1)-(FACTOR-1));
        if (temp > 0 && state == DogState::JUMPING_UP) state = DogState::JUMPING_DOWN;
        sprite.SetSubRect(frames[state == DogState::JUMPING_UP ? DogFrame::JUMP_UP : DogFrame::JUMP_DOWN]);
        sprite.Move(0, temp);
    }
    else {
        setState(DogState::IDLE);
    }
}

void Dog::rise(uint8_t num_of_ducks)
{
    if (num_of_ducks > 2 || num_of_ducks < 0) throw std::out_of_range("Too many or too few ducks!");


}

void Dog::updateAnimation()
{
    if (state == DogState::WALKING) {
        sprite.SetSubRect(frames[DogFrame((int(5*animationtimer.GetElapsedTime())%3)+2)]);
    }
}
