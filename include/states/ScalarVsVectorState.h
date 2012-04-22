#ifndef SCALARVSVECTORSTATE_H
#define SCALARVSVECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

const int HARRIER_SCALE = 3;
const int HARRIER_MOVE_SPEED = 8;

class ScalarVsVectorState : public State
{
    public:
        ScalarVsVectorState();
        ~ScalarVsVectorState() {}

        void input();
        void logic();
        void render() const;

    private:
        //A sprite representing the unnamed character from Space Harrier, an old
        //arcade game.
        Sprite harrier;

        //Displays how far we've travelled and how far we are from the center
        StringGraphic harrierstats;

        //A line that will illustrate displacement
        Shape centerline;

        //How much distance the harrier has travelled.
        uint64_t distance;

        //Whether the Harrier is moving in a certain direction (we use an enum for indices)
        bool ismoving[4];

        //How far the Harrier can move before he collides with the edges.
        float buffer[4];

        //Lets us turn anything printable into a string
        std::ostringstream stats_to_string;

};




#endif // SCALARVSVECTORSTATE_H
