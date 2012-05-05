#ifndef DOG_H
#define DOG_H

#include "../../Declarations.h"

enum class DogFrame : char {
    SNIFF_1 ,   SNIFF_2  ,
    WALK_1  ,   WALK_2   ,   WALK_3,
    EXCITED ,
    JUMP_UP ,   JUMP_DOWN,
    ONE_DUCK,   TWO_DUCKS,
    ONE_SKI ,   TWO_SKI  ,
    LAUGH_1 ,   LAUGH_2  ,
};

enum class DogState : char {
    IDLE        ,
    WALKING     ,
    JUMPING     ,
    HOLDING_DUCK,
};

namespace std {
    template<> struct hash<DogFrame> {
        std::size_t operator()(const DogFrame df) const
        { return hash<char>()(static_cast<char>(df)); }
    };
}

class Dog
{
    public:
        Dog();
        ~Dog();
        void animate();

        Sprite& getSprite()                    { return sprite;    }
        DogState getState() const              { return state;     }
        void setState(const DogState newstate) { state = newstate; }

    private:

        void walk();

        void jump();

        uint8_t frame;

        std::unordered_map<DogFrame, RectInt> frames;

        Timer actiontimer;

        Timer animationtimer;

        Sprite sprite;

        DogState state;
};

#endif // DOG_H
