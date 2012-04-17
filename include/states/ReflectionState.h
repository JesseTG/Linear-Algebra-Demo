#ifndef REFLECTIONSTATE_H
#define REFLECTIONSTATE_H

#include "../State.h"


class ReflectionState : public State
{
    public:
        ReflectionState();
        ~ReflectionState();

        void input();
        void logic();
        void render() const;

    private:
};

#endif // REFLECTIONSTATE_H
