#ifndef DUCK_H
#define DUCK_H

#include "../../Declarations.h"

class Duck
{
    public:
        Duck();
        virtual ~Duck();

        void fly();
        void flyAway();
        Sprite& getSprite() { return sprite; }

    protected:
        Sprite sprite;
        bool is_ski;
        float probChangeDir;
        int speed;
};

#endif // DUCK_H
