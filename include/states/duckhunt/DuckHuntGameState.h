#ifndef DUCKHUNTGAMESTATE_H
#define DUCKHUNTGAMESTATE_H

#include <utility>
#include <vector>

#include "Dog.h"
#include "Duck.h"
#include "../../Declarations.h"
#include "../../State.h"

class Dog;
class Duck;

enum class DuckHuntSound : char {
    DUCK_FALL,
    FAIL     ,
    SUCCEED  ,
    FLAP     ,
    QUACK    ,
    SHOT     ,
    INTRO    ,
};

enum class InGameState : char {
    INTRO      ,
    GAME       ,
    ROUND_START,
    ROUND_END  ,
    ROUND_WIN  ,
    ROUND_FAIL ,
    GAME_OVER  ,
};

enum class HUDStat : char {
    AMMO     ,
    GAME_OVER,
    ROUND    ,
    SCORE    ,
    STATS    ,
    QUOTA    ,
};
//TODO: ROUND_OVER is same no matter how many ducks were shot, relies on other variables

namespace std {
    template<> struct hash<DuckHuntSound> {
        std::size_t operator()(const DuckHuntSound dhs) const
        { return hash<char>()(static_cast<char>(dhs)); }
    };
}

namespace std {
    template<> struct hash<HUDStat> {
        std::size_t operator()(const HUDStat huds) const
        { return hash<char>()(static_cast<char>(huds)); }
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
        //Methods  /////////////////////////////////////////////////////////////////////////////////////////////////////
        //Sets the game's state and resets the timer
        void setState(const InGameState newstate) {
            state = newstate;
            timepassed.Reset();
        }

        //Actual gameplay
        void game();

        //The game has ended, since you've missed too many times!
        void game_over();

        void initSki() {
            for (auto& i : ducks) i.initSki();
            dog.initSki();
        }

        //The introductory animation
        void intro();

        //The instantaneous state that ends the round (cleans up and prepares for the next)
        void round_end();

        //We missed both ducks.
        void round_fail();

        //The instantaneous state that starts the round (initializes values, sets object states, etc.)
        void round_start();

        //We've won the round!
        void round_win();

        //Called by input(); sees if a duck was hit
        void shoot();
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Member variables  ////////////////////////////////////////////////////////////////////////////////////////////
        //How much ammunition we have left
        int8_t                                     ammo;

        //The image that represents the background layers
        Image                                      bglayersimage;

        //The actual visible background layers
        std::array<Sprite, 3>                      bglayers;

        //True if the left mouse button is held down this frame
        bool                                       button_down;

        //True if the left mouse button was held down the previous frame
        bool                                       button_last_down;

        //Whether the user is allowed to shoot or not
        bool                                       can_shoot;

        //The crosshair that shows instead of the cursor
        Sprite                                     crosshair;

        //Whether the dog is behind the grass
        bool                                       dog_behind_grass;

        //The dog that annoys the player
        Dog                                        dog;

        //The ducks in this minigame
        std::array<Duck, 2>                        ducks;

        //How many ducks the user has shot dead this round
        uint8_t                                    ducks_dead;

        //How long the screen remains white when clicked
        Timer                                      flashtimer;

        //The font we use for the stats we keep track of
        Font                                       font;

        //Contains the visible text that covers everything shown in the HUD (ammo, etc.)
        std::unordered_map<HUDStat, StringGraphic> hudstats;

        //If true, the screen is white
        bool                                       is_screen_flash;

        //How many times the player can fall below quota until game over
        uint8_t                                    miss_left;

        //The previous state
        InGameState                                prevstate;

        //Pointers to all objects to render; this time, objects will change layer
        std::vector<sf::Drawable*>                 renderlist;

        //What round we're on
        uint16_t                                   round;

        //The score for this game
        uint32_t                                   score;

        //The sounds that this screen owns (music, etc.)
        std::unordered_map<DuckHuntSound, Sound>   sounds;

        //The state of the game (a state within a state?)
        InGameState                                state;

        //How long the player took to shoot the ducks
        float                                      time_used;

        //How much time has passed; when it hits 5, the ducks fly away
        Timer                                      timepassed;

        //How many ducks since the beginning the user has shot
        uint32_t                                   total_shot;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

#endif // DUCKHUNTGAMESTATE_H
