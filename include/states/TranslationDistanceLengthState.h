#ifndef TRANSLATIONDISTANCELENGTHSTATE_H
#define TRANSLATIONDISTANCELENGTHSTATE_H

#include "../Declarations.h"
#include "../State.h"

//"LEFT/RIGHT" refer to whichever foot is higher
enum class HeroFrame : char {
    NORTH_LEFT,  NORTH_RIGHT,
    SOUTH_LEFT,  SOUTH_RIGHT,
    EAST_LEFT ,  EAST_RIGHT ,
    WEST_LEFT ,  WEST_RIGHT ,
};

//Needed so I can define a hash for enum classes.  Kind of like ID numbers.  ///
namespace std {
    template<> struct hash<HeroFrame> {
        std::size_t operator()(const HeroFrame hf) const
        { return hash<char>()(static_cast<char>(hf)); }
    };
}
////////////////////////////////////////////////////////////////////////////////

class TranslationDistanceLengthState : public State
{
    public:
        TranslationDistanceLengthState();
        ~TranslationDistanceLengthState();

        void input();
        void logic();
        void render();

    private:
        //Used to time the Hero's animation
        Timer                                  animationtimer;

        //How much space the Hero has until he stops moving.
        float                                  buffer[4];

        //Reperesents the frame.  Evens mean left foot is up, odds mean right.
        char                                   frame;

        //The Ghost that follows the mouse.  (That's really the monster's name)
        Sprite                                 ghost;

        //Stores the rectangles that hold the frames in the spritesheet
        std::unordered_map<HeroFrame, RectInt> heroframes;

        //The sprite that represents the hero.
        Sprite                                 hero;

        //Whether the Hero is moving in the four cardinal directions.
        bool                                   ismoving[4];

        //The display for several numerical bits of info
        StringGraphic                          stats;

        //Lets us put the stats inside the StringGraphic
        std::ostringstream                     stats_to_text;

};

#endif // TRANSLATIONDISTANCELENGTHSTATE_H
