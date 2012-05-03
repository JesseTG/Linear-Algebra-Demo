#include  "../../include/states/VectorState.h"

const int TETRAD_SCALE = 8;
const int TETRAD_SPEED = 2;

VectorState::VectorState()
{
    //Setting up the tetrad sprite  ////////////////////////////////////////////
    initSprite(tetrad, sprites, RectInt(16, 0, 39, 15), TETRAD_SCALE,
               VectorFloat(Window.GetWidth()/4, 5*Window.GetHeight()/6)),

    tetradmovement = VectorFloat(TETRAD_SPEED, -TETRAD_SPEED);
    ////////////////////////////////////////////////////////////////////////////

    //Setting up the line that the tetrad travels along  ///////////////////////
    pathline = Shape::Line(Window.GetWidth()/4, 5*Window.GetHeight()/6,
                           Window.GetWidth()*.75, Window.GetHeight()/6,
                           3, Color::White);
    ////////////////////////////////////////////////////////////////////////////

    vectortitle.SetText("Vectors\n\n"
                        "GFX: Tetris (Tengen, 1989)");
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
    stats_to_string << "Position: (" << tetrad.GetPosition().x << ", "
                    << tetrad.GetPosition().y << ")\nVelocity: ("
                    << tetradmovement.x << ", " << tetradmovement.y
                    << ")";
    tetradstats.SetText(stats_to_string.str());
}

void VectorState::render()
{
    Window.Draw(bg);
    Window.Draw(pathline);
    Window.Draw(tetrad);
    Window.Draw(vectortitle);
    Window.Draw(tetradstats);
    Window.Display();
}
