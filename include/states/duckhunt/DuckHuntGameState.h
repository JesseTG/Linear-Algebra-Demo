#ifndef DUCKHUNTGAMESTATE_H
#define DUCKHUNTGAMESTATE_H

#include <list>
#include <memory>

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
        //The introductory screen
        void intro();

        //Called by input(); sees if a duck was hit
        void shoot();

        //The image that represents the background layers
        Image bglayersimage;

        //The actual visible background layers
        Sprite bglayers[3];

        //Whether the user is allowed to shoot or not
        bool can_shoot;

        //The dog that annoys the player
        Dog dog;

        //The pointers to the ducks
        Duck ducks[2];

        //How long the screen remains white when clicked
        Timer flashtimer;

        //If true, the screen is white
        bool is_screen_flash;

        //Pointers to all objects to render; this time, objects will change layer
        std::list<sf::Drawable*> renderlist;

        //What round we're on
        int round;

        //The score for this game
        int score;

        std::unordered_map<DuckHuntSound, Sound> sounds;

        //How much time has passed; when it hits 5, the ducks fly away
        Timer timepassed;




};

#endif // DUCKHUNTGAMESTATE_H
