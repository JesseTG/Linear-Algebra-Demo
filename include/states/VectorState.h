#ifndef VECTORSTATE_H
#define VECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

#include <sstream>

const int TETRAD_SCALE = 8;
const int TETRAD_SPEED = 2;

class VectorState : public State
{
    public:
        VectorState();
        ~VectorState();

        void input();
        void logic();
        void render() const;

    private:
        Shape pathline;
        Sprite tetrad;
        sf::String vectortitle;
        sf::String tetradstats;
        std::ostringstream stats_to_string;
        VectorFloat tetradmovement;
};

VectorState::VectorState()
{
    logger.log("Entering Vectors state.");

    setNextState(StateName::NADA);

    //Setting up the tetrad sprite  ////////////////////////////////////////////
    tetrad.SetImage(sprites);
    tetrad.SetSubRect(RectInt(16, 0, 39, 15));
    tetrad.SetCenter(tetrad.GetSubRect().GetWidth()/2,
                     tetrad.GetSubRect().GetHeight()/2);
    tetrad.SetScale(TETRAD_SCALE, TETRAD_SCALE);
    tetrad.SetPosition(Window.GetWidth()/4, Window.GetHeight()*.8333);
    tetradmovement = VectorFloat(TETRAD_SPEED, -TETRAD_SPEED);
    ////////////////////////////////////////////////////////////////////////////

    //Setting up the line that the tetrad travels along  ///////////////////////
    pathline = Shape::Line(Window.GetWidth()/4, 5*Window.GetHeight()/6,
                           Window.GetWidth()*.75, Window.GetHeight()/6,
                           3, Color::White);
    ////////////////////////////////////////////////////////////////////////////

    vectortitle.SetText("Vectors");
    vectortitle.SetPosition(8, 8);

    tetradstats.SetPosition(Window.GetWidth()/2, 5*Window.GetHeight()/6);
}

VectorState::~VectorState()
{
    logger.log("Exiting Vectors state.");
}

void VectorState::input()
{
    while (Window.GetEvent(event)) {
        if (event.Type == sf::Event::KeyPressed)
            switch (event.Key.Code) {
                case sf::Key::O: setNextState(StateName::TITLE); return;
                case sf::Key::P: setNextState(StateName::SCALARS_VS_VECTORS); return;
            }
    }
}


void VectorState::logic()
{
    //Moving the tetrad  ///////////////////////////////////////////////////////
    if (tetrad.GetPosition().x > Window.GetWidth()*.75 ||
        tetrad.GetPosition().x < Window.GetWidth()/4)
        tetradmovement = -tetradmovement;
    tetrad.Move(tetradmovement);
    ////////////////////////////////////////////////////////////////////////////

    //Displaying the tetrad's info  ////////////////////////////////////////////
    stats_to_string.str("");
    stats_to_string << "Position: (" << int(tetrad.GetPosition().x) << ", "
                    << int(tetrad.GetPosition().y) << ")\nVelocity: ("
                    << int(tetradmovement.x) << ", " << int(tetradmovement.y)
                    << ")";
    tetradstats.SetText(stats_to_string.str());
}

void VectorState::render() const
{
    Window.Draw(bg);
    Window.Draw(pathline);
    Window.Draw(tetrad);
    Window.Draw(vectortitle);
    Window.Draw(tetradstats);
    Window.Display();
}

#endif // VECTORSTATE_H
