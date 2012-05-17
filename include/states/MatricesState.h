#ifndef MATRICESSTATE_H
#define MATRICESSTATE_H

#include "../Declarations.h"
#include "../State.h"

//This state shows a few matrices on-screen.  Nothing big.
class MatricesState : public State
{
    public:
        MatricesState();
        ~MatricesState() {}

        void input();
        void logic() {}  //No logic here, so we can leave this blank.
        void render();

    private:
        //The font used for this screen (it must be fixed-width, the default isn't)
        Font          matrixfont;

        //Shows the matrices on-screen
        StringGraphic text;
};

#endif // MATRICESSTATE_H
