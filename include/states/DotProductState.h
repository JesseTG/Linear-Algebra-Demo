#ifndef DOTPRODUCTSTATE_H
#define DOTPRODUCTSTATE_H

#include "../Declarations.h"
#include "../State.h"


class DotProductState : public State
{
    public:
        DotProductState();
        ~DotProductState() {}

        void input();
        void logic();
        void render();

    private:
        //The angle that the mouse is from the Blue Falcon
        float                   angletomouse;

        //The Blue Falcon's own image file
        Image                   bfsprites;

        //The Blue Falcon itself
        Sprite                  bluefalcon;

        //How much buffer room the BF has before it stops at the edge
        float                   buffer[4];

        //The available frames for the Blue Falcon
        std::array<RectInt, 32> frames;

        //Whether the Blue Falcon is moving
        bool                    ismoving[4];

        //Displays information such as angle, etc.
        StringGraphic           stats;

        //Converts numbers and etc. into text
        std::ostringstream      stats_to_string;
};

#endif // DOTPRODUCTSTATE_H
