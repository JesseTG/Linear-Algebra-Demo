#ifndef ROTATIONSTATE_H
#define ROTATIONSTATE_H

#include <array>

#include "../../Declarations.h"
#include "../../State.h"


class RotationState : public State
{
    public:
        RotationState();
        ~RotationState();

        void input();
        void logic();
        void render() const;

    private:
        //How much room the helicopter has until it stops at the edges
        float buffer[4];

        //Stores the helicopter's current frame
        uint8_t currentframe;

        //Stores each of the four frames the helicopter can have
        std::array<RectInt, 4> frames;

        //The heicopter itself
        Sprite helicopter;


};

#endif // ROTATIONSTATE_H
