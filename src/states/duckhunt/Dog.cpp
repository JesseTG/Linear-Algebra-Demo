#include "../../../include/states/duckhunt/Dog.h"

const int DOG_SCALE = 2;
const float FACTOR = 2;
const float DOG_RISE_SPEED = 1.35;  //How fast the dog rises

Dog::Dog()
{
    {  //Set up the dog's frames of animation
    frames[DogFrame::SNIFF_1  ] = RectInt(  3, 239,  56, 281);
    frames[DogFrame::SNIFF_2  ] = RectInt( 59, 239, 114, 281);
    frames[DogFrame::WALK_1   ] = RectInt(119, 233, 170, 281);
    frames[DogFrame::WALK_2   ] = RectInt(174, 233, 227, 281);
    frames[DogFrame::WALK_3   ] = RectInt(230, 233, 282, 281);
    frames[DogFrame::EXCITED  ] = RectInt(  2, 286,  55, 334);
    frames[DogFrame::JUMP_UP  ] = RectInt( 62, 282,  97, 328);
    frames[DogFrame::JUMP_DOWN] = RectInt(104, 296, 137, 328);
    frames[DogFrame::ONE_DUCK ] = RectInt(  1, 337,  44, 376);
    frames[DogFrame::TWO_DUCK ] = RectInt( 45, 337, 101, 376);
    frames[DogFrame::LAUGH_1  ] = RectInt(102, 335, 131, 374);
    frames[DogFrame::LAUGH_2  ] = RectInt(133, 335, 162, 374);
    }

    {  //Set up the dog's sounds
    sounds[DogSound::SUCCESS].Load("./sfx/duckhunt/success.wav");
    sounds[DogSound::FAIL   ].Load("./sfx/duckhunt/fail.wav"   );
    sounds[DogSound::BARK   ].Load("./sfx/duckhunt/bark.wav"   );
    }

    {  //Set up the dog's actual sprite
    initSprite(sprite,
               sprites,
               frames[DogFrame::SNIFF_1],
               DOG_SCALE,
               VectorFloat(SCREEN.GetWidth()*.1, SCREEN.GetHeight()*.7)
               );
    }

    //The dog barks three times in the intro
    barks = 3;

    setState(DogState::WALKING);
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

void Dog::initSki()
{
    //Now for Mr. Ski mode...
    frames[DogFrame::ONE_DUCK] = RectInt(167, 326, 210, 374);
    frames[DogFrame::TWO_DUCK] = RectInt(213, 326, 267, 374);
}

void Dog::jump()
{
    if (actiontimer.GetElapsedTime() <= 1 && state == DogState::JUMPING_UP) {
        sprite.SetSubRect(frames[DogFrame::EXCITED]);
    }
    else if (actiontimer.GetElapsedTime() <= FACTOR + .2) {
        if (sounds[DogSound::BARK].getStatus() == sf::Sound::Stopped && barks > 0) {
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
    else if (actiontimer.GetElapsedTime() > 2.65) {
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
    }  //And then he lowers again
    else if (actiontimer.GetElapsedTime() >= 1.65 && actiontimer.GetElapsedTime() <= 2.65) {
        sprite.Move(0, DOG_RISE_SPEED);
    }  //Now he's idle, we begin the next round
    else if (actiontimer.GetElapsedTime() > 2.65) {
        setState(DogState::IDLE);
    }
}

void Dog::walk()
{
    sprite.SetSubRect(frames[DogFrame((int(5*actiontimer.GetElapsedTime())%3)+2)]);
    sprite.Move(5.0/7.0, 0);  //Move along closer to the center of the screen
}
