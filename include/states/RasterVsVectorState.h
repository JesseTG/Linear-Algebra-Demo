#ifndef RASTERVSVECTORSTATE_H
#define RASTERVSVECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

//This screen shows two blue pulsating circles, one made of pixels and one that looks like it's made of lines
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
        Sprite        rastercircle;

        //The title of this screen
        StringGraphic rastertitle;

        //Affects the scale of the circles
        Timer         scaletimer;

        //A circle created with sf::Shape
        Shape         vectorcircle;
};

#endif // RASTERVSVECTORSTATE_H
