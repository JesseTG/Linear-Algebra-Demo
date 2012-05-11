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
    AMMO ,
    SCORE,
    ROUND,
    QUOTA,
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
        //The introductory animation
        void intro();

        //Actual gameplay
        void game();

        void setState(const InGameState newstate) {
            state = newstate;
            timepassed.Reset();
        }

        void round_start();

        void round_end();

        void round_win();

        void round_fail();

        //The game has ended, since you've missed too many times!
        void game_over();

        //Called by input(); sees if a duck was hit
        void shoot();

        //The image that represents the background layers
        Image bglayersimage;

        //The actual visible background layers
        std::array<Sprite, 3> bglayers;

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
        std::array<Duck, 2> ducks;

        Font font;

        StringGraphic stats;

        //How long the screen remains white when clicked
        Timer flashtimer;

        //If true, the screen is white
        bool is_screen_flash;

        //Pointers to all objects to render; this time, objects will change layer
        std::vector<sf::Drawable*> renderlist;

        std::unordered_map<HUDStat, StringGraphic> hudstats;

        Sprite crosshair;

        //How much ammunition we have left
        int8_t ammo;

        //How long the player took to shoot the ducks
        float time_used;

        //How many ducks the user has shot dead this round
        uint8_t ducks_dead;

        //How many times the player can fall below quota until game over
        uint8_t miss_left;

        //How many ducks since the beginning the user has shot
        uint32_t total_shot;

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
