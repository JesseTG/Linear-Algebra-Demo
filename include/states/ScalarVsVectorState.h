#ifndef SCALARVSVECTORSTATE_H
#define SCALARVSVECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

//This screen shows the Harrier from Space Harrier flying around the screen with the arrow keys
class ScalarVsVectorState : public State
{
    public:
        ScalarVsVectorState();
        ~ScalarVsVectorState() {}

        void input();
        void logic();
        void render();

    private:
        //How far the Harrier can move before he collides with the edges.
        float              buffer[4];

        //A line that will illustrate displacement
        Shape              centerline;

        //How much distance the harrier has travelled.
        uint64_t           distance;

        //A sprite representing the unnamed character from Space Harrier, an old
        //arcade game.
        Sprite             harrier;

        //Displays how far we've travelled and how far we are from the center
        StringGraphic      harrierstats;

        //Whether the Harrier is moving in a certain direction (we use an enum for indices)
        bool               ismoving[4];

        //Lets us turn anything printable into a string
        std::ostringstream stats_to_string;

};
#endif // SCALARVSVECTORSTATE_H
