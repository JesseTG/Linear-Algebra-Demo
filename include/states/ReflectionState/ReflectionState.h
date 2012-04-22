#ifndef REFLECTIONSTATE_H
#define REFLECTIONSTATE_H

#include <memory>

#include "../../State.h"
#include "OpaOpa.h"

class ReflectionState : public State
{
    public:
        ReflectionState();
        ~ReflectionState();

        void input();
        void logic();
        void render() const;


    private:
        std::shared_ptr<OpaOpa> opaopa;

};



class OpaOpaMissile
{
    public:
        OpaOpaMissile(int velocity);
        ~OpaOpaMissile() { delete this; }

        void move();

    private:
        Sprite missile;
        static int count;
};



#endif // REFLECTIONSTATE_H
