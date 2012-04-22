#include  "../../include/states/VectorState.h"

VectorState::VectorState()
{
    //Setting up the tetrad sprite  ////////////////////////////////////////////
    initSprite(tetrad, sprites, RectInt(16, 0, 39, 15), TETRAD_SCALE,
               VectorFloat(Window.GetWidth()/4, Window.GetHeight()*.8333)),

    tetradmovement = VectorFloat(TETRAD_SPEED, -TETRAD_SPEED);
    ////////////////////////////////////////////////////////////////////////////

    //Setting up the line that the tetrad travels along  ///////////////////////
    pathline = Shape::Line(Window.GetWidth()/4, 5*Window.GetHeight()/6,
                           Window.GetWidth()*.75, Window.GetHeight()/6,
                           3, Color::White);
    ////////////////////////////////////////////////////////////////////////////

    vectortitle.SetText("Vectors");
    vectortitle.SetPosition(8, 8);

    tetradstats.SetPosition(center.x, 5*Window.GetHeight()/6);
}

void VectorState::input()
{
    checkForNextState(StateName::TITLE, StateName::SCALARS_VS_VECTORS);
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
