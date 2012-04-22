#ifndef DOTPRODUCTSTATE_H
#define DOTPRODUCTSTATE_H

#include <array>
#include <utility>

#include "../Declarations.h"
#include "../State.h"


class DotProductState : public State
{
    public:
        DotProductState();
        ~DotProductState() {}

        void input();
        void logic();
        void render() const;

    private:
        std::array<RectInt, 32> frames;
        Image bfsprites;
        float angletomouse;
        Sprite bluefalcon;
        bool ismoving[4];
        float buffer[4];
        StringGraphic stats;
        std::ostringstream stats_to_string;
};

#endif // DOTPRODUCTSTATE_H
