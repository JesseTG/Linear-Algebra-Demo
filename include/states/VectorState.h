#ifndef VECTORSTATE_H
#define VECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

#include <sstream>

class VectorState : public State
{
    public:
        VectorState();
        ~VectorState() {}

        void input();
        void logic();
        void render();

    private:
        //The line that shows the path the tetrad follows.
        Shape pathline;

        //The tetrad itself
        Sprite tetrad;

        //The stringstream that puts the statistics to text
        std::ostringstream stats_to_string;

        //Constantly added to tetrad's position
        VectorFloat tetradmovement;

        //Displays tetrad's position and velocity
        StringGraphic tetradstats;

        //The title for this screen
        StringGraphic vectortitle;
};



#endif // VECTORSTATE_H
