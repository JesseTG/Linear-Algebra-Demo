#include "../../include/states/RasterVsVectorState.h"

RasterVsVectorState::RasterVsVectorState()
{

    //Sets up the raster circle (aka the circle with pixels).  /////////////////
    initSprite(rastercircle, sprites, RectInt(0, 16, 32, 48), VectorFloat(1, 1),
               VectorFloat(Window.GetWidth()/4, center.y));
    ////////////////////////////////////////////////////////////////////////////

    vectorcircle = Shape::Circle(Window.GetWidth()*.75, center.y, 16, Color::Blue);


    scalevector = VectorFloat(1.01, 1.01);

    rastertitle.SetText("Raster Vs. Vector Graphics");
}

void RasterVsVectorState::input()
{
    checkForNextState(StateName::SCALARS_VS_VECTORS, StateName::MATRICES);
}

void RasterVsVectorState::logic()
{
    //We're scaling both circles.  First we decide how big the scaling vector  /
    //will be so we can properly handle the pulsing.  //////////////////////////
    if (rastercircle.GetScale().x > 6)
        scalevector = VectorFloat(2, 2) - scalevector;
    else if (rastercircle.GetScale().x < .5)
        scalevector = VectorFloat(2, 2) - scalevector;
    ////////////////////////////////////////////////////////////////////////////

    //Then we actually scale the circles.  Unfortunately I have to create  /////
    //another circle each frame, even though it's not very efficient.  /////////
    rastercircle.Scale(scalevector);
    vectorcircle = Shape::Circle(Window.GetWidth()*.75, center.y,
                                 16*rastercircle.GetScale().x, Color::Blue);
    ////////////////////////////////////////////////////////////////////////////

}

void RasterVsVectorState::render() const
{
    Window.Draw(bg);
    Window.Draw(rastercircle);
    Window.Draw(vectorcircle);
    Window.Draw(rastertitle);
    Window.Display();
}
