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
        Sprite rastercircle;
        Shape vectorcircle;
        Timer scaletimer;
        StringGraphic rastertitle;
};

#endif // RASTERVSVECTORSTATE_H
