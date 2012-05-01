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

        void setShoot(const bool newcan_shoot);

    private:
        Timer timepassed;
        Timer flashtimer;
        bool can_shoot;
        int round;
        int score;
        Image bglayersimage;
        Sprite bglayers[3];
        std::shared_ptr<Duck> ducks[2];
};

#endif // DUCKHUNTGAMESTATE_H
