#ifndef RASTERVSVECTORSTATE_H
#define RASTERVSVECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"


class RasterVsVectorState : public State
{
    public:
        RasterVsVectorState();
        ~RasterVsVectorState();
        void input();
        void logic();
        void render() const;

    private:
        Sprite rastercircle;
        Shape vectorcircle;
        VectorFloat scalevector;

        StringGraphic rastertitle;
};

#endif // RASTERVSVECTORSTATE_H
