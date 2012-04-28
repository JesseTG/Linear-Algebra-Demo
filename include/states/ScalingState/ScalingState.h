#ifndef SCALINGSTATE_H
#define SCALINGSTATE_H

#include "../../../include/State.h"


class ScalingState : public State
{
    public:
        ScalingState();
        virtual ~ScalingState();

        void input();
        void logic();
        void render() const;

    private:
};

#endif // SCALINGSTATE_H
