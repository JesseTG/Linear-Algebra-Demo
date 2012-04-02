#ifndef SCALARVSVECTORSTATE_H
#define SCALARVSVECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

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

        //Displays how far we've travelled and how far we are from the center
        sf::String harrierstats;

        //A line that will illustrate displacement
        Shape centerline;

        //How much distance the harrier has travelled.
        uint64_t distance;

        //Whether the Harrier is moving in a certain direction (we use an enum for indices)
        bool ismoving[4];

        //How far the Harrier can move before it collides with the edges.
        float buffer[4];

        std::ostringstream stats_to_string;

};

ScalarVsVectorState::ScalarVsVectorState()
{
    logger.log("Entering Scalar Vs. Vectors state.");
    setNextState(StateName::NADA);

    //Set up the Harrier  //////////////////////////////////////////////////////
    harrier.SetImage(sprites);
    harrier.SetSubRect(RectInt(0, 49, 24, 96));
    harrier.SetCenter(harrier.GetSubRect().GetWidth()/2,
                      harrier.GetSubRect().GetHeight()/2);
    harrier.SetScale(HARRIER_SCALE, HARRIER_SCALE);
    harrier.SetPosition(center);

    distance = 0;

    buffer[UP] = harrier.GetSize().y/2;
    buffer[DOWN] = Window.GetHeight() - buffer[UP];
    buffer[LEFT] = harrier.GetSize().x/2;
    buffer[RIGHT] = Window.GetWidth() - buffer[LEFT];

    centerline = Shape::Line(harrier.GetPosition(), center, 5, Color::White);
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
                case sf::Key::P: setNextState(StateName::RASTER_VS_VECTOR); return;
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
    //Stores where we are for further calculation
    VectorFloat currentpos = harrier.GetPosition();

    //In C++, false corresponds to 0, true corresponds to 1.  Very useful for
    //shrinking down code (multiplication is more concise than conditionals).
    harrier.Move(0, -HARRIER_MOVE_SPEED * ismoving[UP] * (harrier.GetPosition().y > buffer[UP]));
    harrier.Move(0, HARRIER_MOVE_SPEED * ismoving[DOWN] * (harrier.GetPosition().y < buffer[DOWN]));
    harrier.Move(-HARRIER_MOVE_SPEED * ismoving[LEFT] * (harrier.GetPosition().x > buffer[LEFT]), 0);
    harrier.Move(HARRIER_MOVE_SPEED * ismoving[RIGHT] * (harrier.GetPosition().x < buffer[RIGHT]), 0);

    //Adds the distance we just moved to the running total
    currentpos -= harrier.GetPosition();
    distance += sqrt(currentpos.x*currentpos.x + currentpos.y*currentpos.y);

    //Changes the harrier's sprite based on which third of the screen he's in  /
    if (harrier.GetPosition().x < Window.GetWidth()/3) {
        harrier.SetSubRect(RectInt(25, 49, 48, 96));
        harrier.FlipX(true);
    }
    else if (harrier.GetPosition().x >= Window.GetWidth()/3 &&
             harrier.GetPosition().x <= 2*Window.GetWidth()/3) {
        harrier.SetSubRect(RectInt(0, 49, 24, 96));
        harrier.FlipX(false);  //The Harrier faces the center
    }
    else if (harrier.GetPosition().x > 2*Window.GetWidth()/3) {
        harrier.SetSubRect(RectInt(25, 49, 48, 96));
        harrier.FlipX(false);
    }
    ////////////////////////////////////////////////////////////////////////////


    //Prepares all statistics for output on-screen  ////////////////////////////
    VectorFloat distancetocenter = harrier.GetPosition() - center;
    stats_to_string.str("");
    stats_to_string << "Vectors Vs. Scalars\n\nDistance Travelled: " << distance
                    << "\nDisplacement From Center: "
                    << sqrt(distancetocenter.x*distancetocenter.x +
                            distancetocenter.y*distancetocenter.y);
    harrierstats.SetText(stats_to_string.str());
    ////////////////////////////////////////////////////////////////////////////

    /*
     *If the Harrier moved, create a new line that tethers him to the center.
     *Sholudn't have to create a new object, but due to how sf::Shape works I
     *don't have many other options.  At least it works.
     */
    if (currentpos != VectorFloat(0, 0))
        centerline = Shape::Line(harrier.GetPosition(), center, 5, Color::White);
}

void ScalarVsVectorState::render() const
{
    Window.Draw(bg);
    Window.Draw(centerline);
    Window.Draw(harrier);
    Window.Draw(harrierstats);
    Window.Display();
}


#endif // SCALARVSVECTORSTATE_H
