#ifndef TRANSLATIONDISTANCELENGTHSTATE_H
#define TRANSLATIONDISTANCELENGTHSTATE_H

#include <unordered_map>
#include <utility>

#include "../Declarations.h"
#include "../State.h"

const int HERO_SCALE = 6;
const int HERO_MOVE_SPEED = 6;
const int GHOST_SCALE = 3;

//LEFT/RIGHT refer to whichever foot is higher
enum class HeroFrame : char {
    NORTH_LEFT, NORTH_RIGHT,
    SOUTH_LEFT, SOUTH_RIGHT,
    EAST_LEFT, EAST_RIGHT,
    WEST_LEFT, WEST_RIGHT
};

//Needed so I can define a hash for enum classes.  Kind of like ID numbers.  ///
namespace std {
    template<> struct hash<HeroFrame>
    {
        std::size_t operator()(const HeroFrame hf) const
        { return hash<char>()(static_cast<char>(hf)); }
    };
}
////////////////////////////////////////////////////////////////////////////////

typedef std::pair<HeroFrame, RectInt> HeroPair;


class TranslationDistanceLengthState : public State
{
    public:
        TranslationDistanceLengthState();
        ~TranslationDistanceLengthState();

        void input();
        void logic();
        void render() const;

    private:
        std::unordered_map<HeroFrame, RectInt> heroframes;
        sf::Sprite hero;
        sf::Sprite ghost;
        bool ismoving[4];
        float buffer[4];
        bool step;  //Which foot the hero has forward.

};

TranslationDistanceLengthState::TranslationDistanceLengthState()
{
    setNextState(StateName::NADA);

    //Preps the unordered map for easy sprite access  //////////////////////////
    heroframes.insert(HeroPair(HeroFrame::NORTH_LEFT, RectInt(102, 0, 118, 16)));
    heroframes.insert(HeroPair(HeroFrame::NORTH_RIGHT, RectInt(120, 0, 136, 16)));
    heroframes.insert(HeroPair(HeroFrame::SOUTH_LEFT, RectInt(39, 0, 55, 16)));
    heroframes.insert(HeroPair(HeroFrame::SOUTH_RIGHT, RectInt(57, 0, 73, 16)));
    heroframes.insert(HeroPair(HeroFrame::WEST_LEFT, RectInt(88, 0, 100, 16)));
    heroframes.insert(HeroPair(HeroFrame::WEST_RIGHT, RectInt(75, 0, 86, 16)));
    heroframes.insert(HeroPair(HeroFrame::EAST_RIGHT, RectInt(138, 0, 150, 16)));
    heroframes.insert(HeroPair(HeroFrame::EAST_LEFT, RectInt(152, 0, 163, 16)));
    ////////////////////////////////////////////////////////////////////////////

    //Preps the Hero sprite itself  ////////////////////////////////////////////
    hero.SetImage(sprites);
    hero.SetSubRect(heroframes[HeroFrame::SOUTH_LEFT]);
    hero.SetCenter(hero.GetSubRect().GetWidth()/2,
                   hero.GetSubRect().GetHeight()/2);
    hero.SetScale(HERO_SCALE, HERO_SCALE);
    hero.SetPosition(center);

    buffer[UP] = hero.GetSize().y/2;
    buffer[DOWN] = Window.GetHeight() - buffer[UP];
    buffer[LEFT] = hero.GetSize().x/2;
    buffer[RIGHT] = Window.GetWidth() - buffer[LEFT];
    ////////////////////////////////////////////////////////////////////////////

    //Preps the Ghost sprite  //////////////////////////////////////////////////
    ghost.SetImage(sprites);
    ghost.SetSubRect(RectInt(34, 18, 58, 48));
    ghost.SetCenter(ghost.GetSubRect().GetWidth()/2,
                    ghost.GetSubRect().GetHeight()/2);
    ghost.SetScale(GHOST_SCALE, GHOST_SCALE);
    ghost.SetPosition(Window.GetInput().GetMouseX(),
                      Window.GetInput().GetMouseY());
    ////////////////////////////////////////////////////////////////////////////

}

TranslationDistanceLengthState::~TranslationDistanceLengthState()
{

}

void TranslationDistanceLengthState::input()
{
    while (Window.GetEvent(event)) {
        if (event.Type == sf::Event::KeyPressed)
            switch (event.Key.Code) {
                case sf::Key::O: setNextState(StateName::MATRICES); return;
                case sf::Key::P: setNextState(StateName::NADA); return;
            }
    }

    ismoving[UP] = Window.GetInput().IsKeyDown(sf::Key::Up) * !ismoving[LEFT] * !ismoving[RIGHT];
    ismoving[DOWN] = Window.GetInput().IsKeyDown(sf::Key::Down) * !ismoving[LEFT] * !ismoving[RIGHT];
    ismoving[LEFT] = Window.GetInput().IsKeyDown(sf::Key::Left) * !ismoving[UP] * !ismoving[DOWN];
    ismoving[RIGHT] = Window.GetInput().IsKeyDown(sf::Key::Right) * !ismoving[UP] * !ismoving[DOWN];
}

void TranslationDistanceLengthState::logic()
{
    hero.Move(0, -HERO_MOVE_SPEED * ismoving[UP] * (hero.GetPosition().y > buffer[UP]));
    hero.Move(0, HERO_MOVE_SPEED * ismoving[DOWN] * (hero.GetPosition().y < buffer[DOWN]));
    hero.Move(-HERO_MOVE_SPEED * ismoving[LEFT] * (hero.GetPosition().x > buffer[LEFT]), 0);
    hero.Move(HERO_MOVE_SPEED * ismoving[RIGHT] * (hero.GetPosition().x < buffer[RIGHT]), 0);

    hero.SetSubRect()

    ghost.SetPosition(Window.GetInput().GetMouseX(), Window.GetInput().GetMouseY());
}

void TranslationDistanceLengthState::render() const
{
    Window.Draw(bg);
    Window.Draw(hero);
    Window.Draw(ghost);
    Window.Display();
}

#endif // TRANSLATIONDISTANCELENGTHSTATE_H
