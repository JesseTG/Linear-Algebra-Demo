#ifndef ROTATIONSTATE_H
#define ROTATIONSTATE_H

#include <array>
#include <sstream>

#include "../Declarations.h"
#include "../State.h"


class RotationState : public State
{
    public:
        RotationState();
        ~RotationState();

        void input();
        void logic();
        void render();

    private:
        //helicopter's acceleration; added to velocity, calculated by direction
        VectorFloat            acceleration;

        //Used to time the helicopter's animation
        Timer                  animationtimer;

        //The bump that plays whenever we hit the wall
        Sound                  bump;

        //Stores each of the four frames the helicopter can have
        std::array<RectInt, 4> frames;

        //The heicopter itself
        Sprite                 helicopter;

        //Shows the screen's information
        StringGraphic          stats;

        //Converts numbers, etc. to string
        std::ostringstream     stats_to_string;

        //helicopter's velocity; added to position
        VectorFloat            velocity;
};

#endif // ROTATIONSTATE_H
