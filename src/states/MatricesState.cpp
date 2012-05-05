#include "../../include/states/MatricesState.h"

MatricesState::MatricesState()
{
    matrixfont.LoadFromFile("./gfx/emulogic.ttf");
    text.SetFont(matrixfont);
    text.SetSize(24);
    text.SetPosition(16, 16);
    text.SetText("Matrices\n\n"
                 "Easily Multipliable    \n  "
                 "[30 12  3]   [ 1  3  9]\n  "
                 "[10  9  2] x [17  4  6]\n  "
                 "[ 0  0  1]   [ 0  0  1]\n\n\n"
                 "Painfully Multipliable \n  "
                 "[ 6 10]   [ 3 12  4]   \n  "
                 "[40  1] x [ 7  9  8]   \n  "
                 "[ 2 13]                \n\n\n"
                 "Not Multipliable       \n  "
                 "[10 13 94]   [ 1  3]   \n  "
                 "[14  4 28] x [45  8]   \n  "
                 "[91  0  1]             \n  ");

    Window.Draw(bg  );
    Window.Draw(text);
    Window.Display();
}

void MatricesState::input()
{
    checkForNextState(StateName::RASTER_VS_VECTOR, StateName::TRANSLATION);
}
