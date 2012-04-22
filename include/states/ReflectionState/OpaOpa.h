#ifndef OPAOPA_H
#define OPAOPA_H

#include "../../Declarations.h"

class OpaOpa  //The name of the ship from Fantasy Zone.
{
    public:
        OpaOpa();
        ~OpaOpa();
        void move();
        void shoot();
        Sprite& getSprite() { return ship; }

    private:
        Sprite ship;
        float buffer[4];
        bool ismoving[4];
};

#endif // OPAOPA_H
