#include  "../../include/states/VectorState.h"

const int TETRAD_SCALE = 8;
const int TETRAD_SPEED = 2;

VectorState::VectorState()
{
    //Setting up the tetrad sprite
    initSprite(tetrad, sprites, RectInt(16, 0, 39, 15), TETRAD_SCALE,
               VectorFloat(SCREEN.GetWidth()/4, 5*SCREEN.GetHeight()/6)),

    tetradmovement = VectorFloat(TETRAD_SPEED, -TETRAD_SPEED);

    //Setting up the line that the tetrad travels along
    pathline = Shape::Line(SCREEN.GetWidth()/4, 5*SCREEN.GetHeight()/6,
                           SCREEN.GetWidth()*.75, SCREEN.GetHeight()/6,
                           3, Color::White);

    //Setting up the text
    vectortitle.SetText("Vectors\n\nGFX: Tetris (Tengen, 1989)");
    vectortitle.SetPosition(8, 8);
    tetradstats.SetPosition(CENTER.x, 5*SCREEN.GetHeight()/6);
}

void VectorState::input()
{
    checkForNextState(StateName::TITLE, StateName::SCALARS_VS_VECTORS);
}

void VectorState::logic()
{
    //Moving the tetrad
    if (tetrad.GetPosition().x > SCREEN.GetWidth()*.75 || tetrad.GetPosition().x < SCREEN.GetWidth()/4)
        tetradmovement = -tetradmovement;
    tetrad.Move(tetradmovement);

    //Displaying the tetrad's info
    stats_to_string.str("");
    stats_to_string << "Position: (" << tetrad.GetPosition().x << ", "
                    << tetrad.GetPosition().y << ")\nVelocity: ("
                    << tetradmovement.x << ", " << tetradmovement.y
                    << ")";
    tetradstats.SetText(stats_to_string.str());
}

void VectorState::render()
{
    Window.Draw(bg         );
    Window.Draw(pathline   );
    Window.Draw(tetrad     );
    Window.Draw(vectortitle);
    Window.Draw(tetradstats);
    Window.Display();
}
