#ifndef MATRICESSTATE_H
#define MATRICESSTATE_H

#include "../Declarations.h"
#include "../State.h"

class MatricesState : public State
{
    public:
        MatricesState();
        ~MatricesState();

        void input();
        void logic() {}  //No logic here, so we can leave this blank.
        void render() const {}  //Only need to render this screen once.

    private:
        StringGraphic text;
        Font matrixfont;
};

#endif // MATRICESSTATE_H
