#ifndef DUCKHUNTTITLE_H
#define DUCKHUNTTITLE_H

#include "../../State.h"

class DuckHuntTitle : public State
{
    public:
        DuckHuntTitle();
        ~DuckHuntTitle();

        void input();
        void logic() {}
        void render() {}

    private:
        Sprite logo;
        Font font;
        StringGraphic text;
        Sound titlejingle;
};

#endif // DUCKHUNTTITLE_H
