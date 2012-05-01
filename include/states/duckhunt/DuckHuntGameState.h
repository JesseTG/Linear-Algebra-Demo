#ifndef DUCKHUNTGAMESTATE_H
#define DUCKHUNTGAMESTATE_H

#include <memory>

#include "Duck.h"
#include "../../State.h"

class Duck;

class DuckHuntGameState : public State
{
    public:
        DuckHuntGameState();
        ~DuckHuntGameState();
        void input();
        void logic();
        void render() const;

    private:
        //Called by input(); sees if a duck was hit
        void shoot();

        //The image that represents the background layers
        Image bglayersimage;

        //The actual visible background layers
        Sprite bglayers[3];

        //Whether the user is allowed to shoot or not
        bool can_shoot;

        //The pointers to the ducks
        std::unique_ptr<Duck> ducks[2];

        //How long the screen remains white when clicked
        Timer flashtimer;

        //What round we're on
        int round;

        //The score for this game
        int score;

        //How much time has passed; when it hits 5, the ducks fly away
        Timer timepassed;




};

#endif // DUCKHUNTGAMESTATE_H
