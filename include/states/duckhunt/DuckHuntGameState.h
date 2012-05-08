#ifndef DUCKHUNTGAMESTATE_H
#define DUCKHUNTGAMESTATE_H


#include <memory>
#include <utility>
#include <vector>

#include "Dog.h"
#include "Duck.h"
#include "../../Declarations.h"
#include "../../State.h"

class Duck;

enum class DuckHuntSound : char {
    DUCK_FALL,
    FAIL     ,
    FLAP     ,
    QUACK    ,
    SHOT     ,
    INTRO    ,
};

enum class InGameState : char {
    INTRO     ,
    GAME      ,
    ROUND_END ,
    ROUND_WIN ,
    ROUND_FAIL,
    GAME_OVER ,
};
//TODO: ROUND_OVER is same no matter how many ducks were shot, relies on other variables

namespace std {
    template<> struct hash<DuckHuntSound> {
        std::size_t operator()(const DuckHuntSound dhs) const
        { return hash<char>()(static_cast<char>(dhs)); }
    };
}

class DuckHuntGameState : public State
{
    public:
        DuckHuntGameState();
        ~DuckHuntGameState();
        void input();
        void logic();
        void render();

    private:
        //The introductory animation
        void intro();

        //Actual gameplay
        void game();


        void round_end();

        void round_win() {}

        void round_fail() {}

        //The game has ended, since you've missed too many times!
        void game_over();

        //Called by input(); sees if a duck was hit
        void shoot();

        //The image that represents the background layers
        Image bglayersimage;

        //The actual visible background layers
        Sprite bglayers[3];

        //Whether the dog is behind the grass
        bool dog_behind_grass;

        //Whether the user is allowed to shoot or not
        bool can_shoot;

        //True if the left mouse button is held down this frame
        bool button_down;

        //True if the left mouse button was held down the previous frame
        bool button_last_down;

        //The dog that annoys the player
        Dog dog;

        //The ducks in this minigame
        Duck ducks[2];

        //How long the screen remains white when clicked
        Timer flashtimer;

        //If true, the screen is white
        bool is_screen_flash;

        //Pointers to all objects to render; this time, objects will change layer
        std::vector<sf::Drawable*> renderlist;

        //How much ammunition we have left
        int8_t ammo;

        //How many ducks the user has shot dead this round
        uint8_t ducks_dead;

        //What round we're on
        uint16_t round;

        //The score for this game
        uint32_t score;

        std::unordered_map<DuckHuntSound, Sound> sounds;

        //The state of the game (a state within a state?)
        InGameState state;

        //The previous state
        InGameState prevstate;

        //How much time has passed; when it hits 5, the ducks fly away
        Timer timepassed;




};

#endif // DUCKHUNTGAMESTATE_H
