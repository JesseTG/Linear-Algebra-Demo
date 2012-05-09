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
        ~Dog();
        void updateAnimation();
        void act();

        Sprite& getSprite()                    { return sprite;    }
        DogState getState() const              { return state;     }
        void setState(const DogState newstate) {
            state = newstate;
            actiontimer.Reset();
        }

    private:

        void walk();

        void jump();

        void rise();

        void laugh();

        int8_t barks;

        std::unordered_map<DogFrame, RectInt> frames;

        std::unordered_map<DogSound, Sound> sounds;

        Timer actiontimer;

        Timer animationtimer;

        Sprite sprite;

        DogState state;

        DogState prevstate;
};

#endif // DOG_H
