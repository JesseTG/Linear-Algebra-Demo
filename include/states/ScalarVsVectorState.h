#ifndef SCALARVSVECTORSTATE_H
#define SCALARVSVECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

#include <sstream>

const int HARRIER_SCALE = 3;
const int HARRIER_MOVE_SPEED = 8;


class ScalarVsVectorState : public State
{
    public:
        ScalarVsVectorState();
        ~ScalarVsVectorState();

        void input();
        void logic();
        void render() const;

    private:
        //A sprite representing the unnamed character from Space Harrier, an old
        //arcade game.
        Sprite harrier;

        //How much distance the harrier has travelled.
        uint64_t distance;

        //Whether the Harrier is moving in a certain direction (we use an enum for indices)
        bool ismoving[4];

        //How far the Harrier can move before it collides with the edges.
        float buffer[4];

        std::ostringstream stats_to_string;

        sf::String harrierstats;
};

ScalarVsVectorState::ScalarVsVectorState()
{
    logger.log("Entering Scalar Vs. Vectors state.");
    setNextState(StateName::NADA);

    //Set up the Harrier's sprite  /////////////////////////////////////////////
    harrier.SetImage(sprites);
    harrier.SetSubRect(RectInt(0, 49, 24, 96));
    harrier.SetCenter(harrier.GetSubRect().GetWidth()/2,
                      harrier.GetSubRect().GetHeight()/2);
    harrier.SetScale(HARRIER_SCALE, HARRIER_SCALE);
    harrier.SetPosition(Window.GetWidth()/2, Window.GetHeight()/2);

    buffer[UP] = harrier.GetSize().y/2;
    buffer[DOWN] = Window.GetHeight() - buffer[UP];
    buffer[LEFT] = harrier.GetSize().x/2;
    buffer[RIGHT] = Window.GetWidth() - buffer[LEFT];
    ////////////////////////////////////////////////////////////////////////////
}

ScalarVsVectorState::~ScalarVsVectorState()
{
    logger.log("Exiting Scalar Vs. Vectors state.");
}

void ScalarVsVectorState::input()
{
    while (Window.GetEvent(event)) {
        if (event.Type == sf::Event::KeyPressed) {
            switch (event.Key.Code) {
                case sf::Key::O: setNextState(StateName::VECTORS); return;
                case sf::Key::P: setNextState(StateName::NADA); return;
            }
        }
    }

    ismoving[UP] = Window.GetInput().IsKeyDown(sf::Key::Up);
    ismoving[DOWN] = Window.GetInput().IsKeyDown(sf::Key::Down);
    ismoving[LEFT] = Window.GetInput().IsKeyDown(sf::Key::Left);
    ismoving[RIGHT] = Window.GetInput().IsKeyDown(sf::Key::Right);
}

void ScalarVsVectorState::logic()
{
    VectorFloat currentpos = harrier.GetPosition();
    //In C++, false corresponds to 0, true corresponds to 1.  Very useful for
    //shrinking down code (multiplication is more concise than conditionals).
    harrier.Move(0, -HARRIER_MOVE_SPEED * ismoving[UP] * (harrier.GetPosition().y > buffer[UP]));
    harrier.Move(0, distance += HARRIER_MOVE_SPEED * ismoving[DOWN] * (harrier.GetPosition().y < buffer[DOWN]));
    harrier.Move(distance += -HARRIER_MOVE_SPEED * ismoving[LEFT] * (harrier.GetPosition().x > buffer[LEFT]), 0);
    harrier.Move(distance += HARRIER_MOVE_SPEED * ismoving[RIGHT] * (harrier.GetPosition().x < buffer[RIGHT]), 0);
    distance += abs(harier.pos)
    //TODO: Implement the distance travelled

    if (harrier.GetPosition().x <= Window.GetWidth()/3) {
        harrier.SetSubRect(RectInt(25, 49, 48, 96));
        harrier.FlipX(true);
    }
    else if (harrier.GetPosition().x > Window.GetHeight()/3 &&
             harrier.GetPosition().x < 2*Window.GetHeight()/3) {
                 harrier.SetSubRect(RectInt(0, 49, 24, 96));
                 harrier.FlipX(false);
    }
    else if (harrier.GetPosition().x >= 2*Window.GetWidth()/3) {
        harrier.SetSubRect(RectInt(25, 49, 48, 96));
        harrier.FlipX(false);
    }

    VectorFloat distancetocenter = VectorFloat(harrier.GetPosition()) - VectorFloat(Window.GetWidth(), Window.GetHeight());
    stats_to_string.str("");
    stats_to_string << "Distance Travelled: " << distance
                    << "\nDistance From Center: "
                    << sqrt(distancetocenter.x*distancetocenter.x +
                            distancetocenter.y*distancetocenter.y);
    harrierstats.SetText(stats_to_string.str());
}

void ScalarVsVectorState::render() const
{
    Window.Draw(bg);
    Window.Draw(harrier);
    Window.Draw(harrierstats);
    Window.Display();
}


#endif // SCALARVSVECTORSTATE_H
