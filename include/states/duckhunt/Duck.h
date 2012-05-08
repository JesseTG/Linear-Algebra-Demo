#ifndef DUCK_H
#define DUCK_H

#include "../../Declarations.h"

enum class DuckFrame : char {
    NORM_1 ,
    NORM_2 ,
    NORM_3 ,
    UP_1   ,
    UP_2   ,
    UP_3   ,
    SHOT   ,
    FALLING,
};

enum class DuckState : char {
    IDLE         ,
    FLYING_IN    ,
    FLYING_AROUND,
    SHOT         ,
    FALLING      ,
    HIT_GROUND   ,
    FLYING_OUT   ,
};

namespace std {
    template<> struct hash<DuckFrame> {
        std::size_t operator()(const DuckFrame df) const
        { return hash<char>()(static_cast<char>(df)); }
    };
}

class Duck
{
    public:
        Duck();
        virtual ~Duck();

        void move();
        void die();

        void act();

        DuckState getState() const { return state; }

        void setState(const DuckState newstate) {
            state = newstate;
            actiontimer.Reset();
        }

        void updateAnimation();

        RectFloat getShotBox() const { return shotbox; }

        Sprite& getSprite() { return sprite; }

    protected:
        //The frames that the ducks can use
        static std::unordered_map<DuckFrame, RectInt> frames;

        //Updates the position of the box we can shoot at
        void updateShotBox();

        //Sets the direction of the duck to be random
        void setRandomDirection();

        //The duck flying into the screen; can't be shot yet!
        void flyIn();

        //The duck flying away; can't be shot anymore!
        void flyOut();

        //The duck flying around; fair game!
        void flyAround();

        //The duck falling; you've shot him already!
        void fall();

        void detectBoundaries();

        Timer actiontimer;

        //Times the duck's animation
        Timer animationtimer;

        //The current frame this duck has
        uint8_t frame;

        //SPEED, not velocity
        static float speed;

        //The box that the cursor has to be in to register a hit
        RectFloat shotbox;

        //The buffer room a duck has before it turns around
        float buffer[4];

        //The actual visible sprite
        Sprite sprite;

        //Whether this duck has been shot dead
        bool is_dead;

        //Whether this is a Mr. Ski duck
        bool is_ski;

        DuckState prevstate;

        DuckState state;

        //The odds of the duck changing velocity (thus direction) each frame
        float probChangeVel;

        //How fast this duck is going on both dimensions
        VectorFloat velocity;

};

#endif // DUCK_H
