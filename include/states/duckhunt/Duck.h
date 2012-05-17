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
    FLYING_OUT   ,
};

enum class DuckSound : char {
    FLAP      ,
    QUACK     ,
    FALL      ,
    HIT_GROUND,
};

namespace std {
    template<> struct hash<DuckFrame> {
        std::size_t operator()(const DuckFrame df) const
        { return hash<char>()(static_cast<char>(df)); }
    };
}

namespace std {
    template<> struct hash<DuckSound> {
        std::size_t operator()(const DuckSound ds) const
        { return hash<char>()(static_cast<char>(ds)); }
    };
}

class Duck
{
    public:
        Duck();
        virtual ~Duck();

        //Makes the ducks harder to hit
        static void increaseDifficulty(const int round) {
            speed = (round/3.0) + 3;
            probChangeVel = ((round+1.0)/(round+2.0))/30.0;
            if (round == 20) initSki();
        }

        //Initializes the ducks for Mr. Ski Mode
        static void initSki();

        //Acts each frame depending on the current state
        void act();

        //Gets the box you have to shoot the duck in
        RectFloat getShotBox() const { return shotbox; }

        //Gets the duck's sprite
        Sprite& getSprite() { return sprite; }

        //Returns the duck's state
        DuckState getState() const { return state; }

        //Sets this duck's state, and resets the actiontimer
        void setState(const DuckState newstate) {
            state = newstate;
            actiontimer.Reset();
        }

        //Updates animation based on the current state
        void updateAnimation();





    protected:
        //Sees if the ducks is at the edge, and ensures he doesn't cross it
        void detectBoundaries();

        //First the duck hovers in the air for a moment, then falls to the ground
        void die();

        //The duck falling; you've shot him already!
        void fall();

        //The duck flying around; fair game!
        void flyAround();

        //The duck flying into the screen; also can be shot!
        void flyIn();

        //The duck flying away; can't be shot anymore!
        void flyOut();

        //Sets the direction of the duck to be random
        void setRandomDirection();

        //Updates the position of the box we can shoot at
        void updateShotBox();

        //The buffer room a duck has before it turns around
        static float                                  buffer[4];

        //The frames that the ducks can use
        static std::unordered_map<DuckFrame, RectInt> frames;

        //The odds of the duck changing velocity (thus direction) each frame
        static float                                  probChangeVel;

        //The sounds that the ducks can play
        static std::unordered_map<DuckSound, Sound>   sounds;

        //SPEED, not velocity, of the ducks
        static float                                  speed;


        Timer       actiontimer;

        //Times the duck's animation
        Timer       animationtimer;

        //The duck's previous state
        DuckState   prevstate;

        //The box that the cursor has to be in to register a hit
        RectFloat   shotbox;

        //The actual visible sprite
        Sprite      sprite;

        //The duck's current state
        DuckState   state;

        //How fast this duck is going on both dimensions
        VectorFloat velocity;
};

#endif // DUCK_H
