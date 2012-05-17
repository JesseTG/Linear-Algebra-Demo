#ifndef DOG_H
#define DOG_H

#include "../../Declarations.h"

enum class DogFrame : char {
    SNIFF_1 ,   SNIFF_2  ,
    WALK_1  ,   WALK_2   ,   WALK_3,
    EXCITED ,
    JUMP_UP ,   JUMP_DOWN,
    ONE_DUCK,   TWO_DUCK ,
    ONE_SKI ,   TWO_SKI  ,
    LAUGH_1 ,   LAUGH_2  ,
};

enum class DogState : char {
    IDLE         ,
    WALKING      ,
    JUMPING_UP   ,
    JUMPING_DOWN ,
    HOLDING_1DUCK,
    HOLDING_2DUCK,
    LAUGHING     ,
};

enum class DogSound : char {
    SUCCESS,
    FAIL   ,
    BARK   ,
};

namespace std {
    template<> struct hash<DogFrame> {
        std::size_t operator()(const DogFrame df) const
        { return hash<char>()(static_cast<char>(df)); }
    };
}

namespace std {
    template<> struct hash<DogSound> {
        std::size_t operator()(const DogSound ds) const
        { return hash<char>()(static_cast<char>(ds)); }
    };
}

class Dog
{
    public:
        Dog();

        //Act based on the current state
        void act();

        //Initialize Mr. Ski mode
        void initSki();

        Sprite& getSprite()                    { return sprite;    }
        DogState getState() const              { return state;     }

        //Resets the Dog's actiontimer when called
        void setState(const DogState newstate) {
            state = newstate;
            actiontimer.Reset();
        }

    private:
        //The dog jumps behind the grass
        void jump();

        //The dog mocks you since you shot no ducks
        void laugh();

        //The dog shows you the ducks you shot
        void rise();

        //The dog walks along the screen
        void walk();

        //The timer that monitors the dog's actions
        Timer                                 actiontimer;

        //The timer that monitors the dog's animation
        Timer                                 animationtimer;

        //How many times the dog barks in the intro
        int8_t                                barks;

        //The available frames the dog has
        std::unordered_map<DogFrame, RectInt> frames;

        //Whether we've got Mr. Ski ducks or not
        bool                                  is_ski;

        //The dog's previous state
        DogState                              prevstate;

        //The sounds the dog is capable of playing
        std::unordered_map<DogSound, Sound>   sounds;

        //The actual visible sprite
        Sprite                                sprite;

        //The dog's current state
        DogState                              state;


};

#endif // DOG_H
