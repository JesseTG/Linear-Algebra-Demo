#ifndef VECTORSTATE_H
#define VECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

#include <sstream>

const int TETRAD_SCALE = 8;
const int TETRAD_SPEED = 2;

class VectorState : public State
{
    public:
        VectorState();
        ~VectorState();

        void input();
        void logic();
        void render() const;

    private:
        Shape pathline;
        Sprite tetrad;
        StringGraphic vectortitle;
        StringGraphic  tetradstats;
        std::ostringstream stats_to_string;
        VectorFloat tetradmovement;
};



#endif // VECTORSTATE_H
