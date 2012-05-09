#include "../../../include/states/duckhunt/Dog.h"

const int DOG_SCALE = 2;
const float FACTOR = 2;
const float DOG_RISE_SPEED = 1.4;  //How fast the dog rises

#include <iostream>

Dog::Dog()
{
    frames[DogFrame::SNIFF_1  ] = RectInt(  3, 233,  56, 275);
    frames[DogFrame::SNIFF_2  ] = RectInt( 59, 233, 114, 275);
    frames[DogFrame::WALK_1   ] = RectInt(119, 233, 170, 275);
    frames[DogFrame::WALK_2   ] = RectInt(173, 233, 226, 275);
    frames[DogFrame::WALK_3   ] = RectInt(230, 233, 282, 275);
    frames[DogFrame::EXCITED  ] = RectInt(  2, 280,  55, 328);
    frames[DogFrame::JUMP_UP  ] = RectInt( 62, 276,  97, 322);
    frames[DogFrame::JUMP_DOWN] = RectInt(104, 290, 137, 322);
    frames[DogFrame::ONE_DUCK ] = RectInt(  1, 331,  44, 370);
    frames[DogFrame::TWO_DUCK ] = RectInt( 45, 331, 101, 370);
    frames[DogFrame::LAUGH_1  ] = RectInt(102, 329, 131, 368);
    frames[DogFrame::LAUGH_2  ] = RectInt(133, 329, 162, 368);

    sounds[DogSound::SUCCESS].file.LoadFromFile("./sfx/duckhunt/success.wav");
    sounds[DogSound::SUCCESS].sound.SetBuffer(sounds[DogSound::SUCCESS].file);
    sounds[DogSound::FAIL   ].file.LoadFromFile("./sfx/duckhunt/fail.wav"   );
    sounds[DogSound::FAIL   ].sound.SetBuffer(sounds[DogSound::FAIL].file   );
    sounds[DogSound::BARK   ].file.LoadFromFile("./sfx/duckhunt/bark.wav"   );
    sounds[DogSound::BARK   ].sound.SetBuffer(sounds[DogSound::BARK].file   );

    initSprite(sprite, sprites, frames[DogFrame::SNIFF_1], DOG_SCALE,
               VectorFloat(Window.GetWidth()*.1, Window.GetHeight()*.70));

    barks = 3;

    setState(DogState::WALKING);
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
        case DogState::HOLDING_1DUCK:
        case DogState::HOLDING_2DUCK: rise();  break;
        case DogState::LAUGHING     : laugh(); break;
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
    else if (actiontimer.GetElapsedTime() <= FACTOR + .2) {
        if (sounds[DogSound::BARK].sound.GetStatus() == sf::Sound::Stopped && barks > 0) {
            --barks;
            sounds[DogSound::BARK].Play();
        }
        float temp = 2*(2*(actiontimer.GetElapsedTime()-1)-(FACTOR-1));
        if (temp > 0 && state == DogState::JUMPING_UP) state = DogState::JUMPING_DOWN;
        sprite.SetSubRect(frames[state == DogState::JUMPING_UP ? DogFrame::JUMP_UP : DogFrame::JUMP_DOWN]);
        sprite.Move(0, temp);
    }
    else {
        setState(DogState::IDLE);
    }
}

void Dog::rise()
{
    if (prevstate == DogState::IDLE) sounds[DogSound::SUCCESS].Play();

    //Changes the dog's sprite based on how many ducks you shot
    if (state == DogState::HOLDING_1DUCK)
        sprite.SetSubRect(frames[DogFrame::ONE_DUCK]);
    else if (state == DogState::HOLDING_2DUCK)
        sprite.SetSubRect(frames[DogFrame::TWO_DUCK]);

    //Now the dog actually rises after brief delay
    if (actiontimer.GetElapsedTime() <= 1) {
        if (prevstate == DogState::IDLE)
            sounds[DogSound::SUCCESS].Play();
        sprite.Move(0, -DOG_RISE_SPEED);
    }
    else if (actiontimer.GetElapsedTime() >= 1.65 && actiontimer.GetElapsedTime() <= 2.65) {
        sprite.Move(0, DOG_RISE_SPEED);
    }


}

void Dog::laugh()
{
    sprite.SetSubRect(frames[(floor(sin(30*actiontimer.GetElapsedTime())) + 1) == 0 ? DogFrame::LAUGH_1 : DogFrame::LAUGH_2]);

    if (actiontimer.GetElapsedTime() <= 1) {
        if (prevstate == DogState::IDLE)
            sounds[DogSound::FAIL].Play();
        sprite.Move(0, -DOG_RISE_SPEED);
    }
    else if (actiontimer.GetElapsedTime() >= 1.65 && actiontimer.GetElapsedTime() <= 2.65) {
        sprite.Move(0, DOG_RISE_SPEED);
    }
}

void Dog::updateAnimation()
{
    if (state == DogState::WALKING) {
        sprite.SetSubRect(frames[DogFrame((int(5*animationtimer.GetElapsedTime())%3)+2)]);
    }
}
