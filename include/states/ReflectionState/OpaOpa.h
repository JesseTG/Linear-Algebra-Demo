#ifndef OPAOPA_H
#define OPAOPA_H

#include <array>

#include "../../Declarations.h"

class OpaOpa  //The name of the ship from Fantasy Zone.
{
    public:
        OpaOpa();
        ~OpaOpa();
        void move();
        void animate();
        void shoot();
        Sprite& getSprite() { return ship; }

    private:
        Sprite ship;
        float buffer[4];
        bool ismoving[4];
        std::array<RectInt, 4> frames;
        Timer animationtimer;
        char currentframe;
};

#endif // OPAOPA_H
