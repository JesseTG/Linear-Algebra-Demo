#include "../../include/states/RasterVsVectorState.h"

RasterVsVectorState::RasterVsVectorState()
{

    //Sets up the raster circle (aka the circle with pixels).  /////////////////
    initSprite(rastercircle, sprites, RectInt(0, 16, 32, 48), 1,
               VectorFloat(SCREEN.GetWidth()/4, CENTER.y));
    ////////////////////////////////////////////////////////////////////////////

    vectorcircle = Shape::Circle(Window.GetWidth()*.75, CENTER.y, 16, Color::Blue);

    rastertitle.SetText("Raster Vs. Vector Graphics");
}

void RasterVsVectorState::input()
{
    checkForNextState(StateName::SCALARS_VS_VECTORS, StateName::MATRICES);
}

void RasterVsVectorState::logic()
{
    //Calculate how much to scale the circles.  Whee, trigonometry!
    float temp = (sin(2*scaletimer.GetElapsedTime()) + 2) * 2;

    //Then we actually scale the circles.  Unfortunately I have to create  /////
    //another circle each frame, even though it's not very efficient.  /////////
    rastercircle.SetScale(temp, temp);
    vectorcircle = Shape::Circle(SCREEN.GetWidth()*.75, CENTER.y, temp*16, Color::Blue);
}

void RasterVsVectorState::render()
{
    Window.Draw(bg          );
    Window.Draw(rastercircle);
    Window.Draw(vectorcircle);
    Window.Draw(rastertitle );
    Window.Display();
}
