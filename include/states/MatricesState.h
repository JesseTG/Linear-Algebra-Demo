#ifndef MATRICESSTATE_H
#define MATRICESSTATE_H

#include "../Declarations.h"
#include "../State.h"

class MatricesState : public State
{
    public:
        MatricesState();
        ~MatricesState() {}

        void input();
        void logic() {}  //No logic here, so we can leave this blank.
        void render() {}  //Only need to render this screen once.

    private:
        //Shows the matrices on-screen
        StringGraphic text;

        //The font used for this screen (it must be fixed-width)
        Font matrixfont;
};

#endif // MATRICESSTATE_H
