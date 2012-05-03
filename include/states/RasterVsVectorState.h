#ifndef RASTERVSVECTORSTATE_H
#define RASTERVSVECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"


class RasterVsVectorState : public State
{
    public:
        RasterVsVectorState();
        ~RasterVsVectorState() {}
        void input();
        void logic();
        void render();

    private:
        //A circle pulled from a sprite sheet
        Sprite rastercircle;

        //A circle created with sf::Shape
        Shape vectorcircle;

        //Affects the scale of the circles
        Timer scaletimer;

        //The title of this screen
        StringGraphic rastertitle;
};

#endif // RASTERVSVECTORSTATE_H
