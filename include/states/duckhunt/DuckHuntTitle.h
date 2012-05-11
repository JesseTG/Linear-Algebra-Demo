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
        void render();

    private:
        //The logo for the original game
        Sprite        logo;

        //The font we use to render the text
        Font          font;

        //The text that invites the user to play
        StringGraphic text;

        //The theme of the original game
        Sound         titlejingle;
};

#endif // DUCKHUNTTITLE_H
