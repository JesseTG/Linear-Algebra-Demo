#ifndef RASTERVSVECTORSTATE_H
#define RASTERVSVECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"


class RasterVsVectorState : public State
{
    public:
        RasterVsVectorState();
        ~RasterVsVectorState();
        void input();
        void logic();
        void render() const;

    private:
        sf::Sprite rastercircle;
        sf::Shape vectorcircle;
        VectorFloat scalevector;

        sf::String rastertitle;
};

RasterVsVectorState::RasterVsVectorState()
{
    logger.log("Entered Raster Vs. Vector state.");
    setNextState(StateName::NADA);

    //Sets up the raster circle (aka the circle with pixels).  /////////////////
    rastercircle.SetImage(sprites);
    rastercircle.SetSubRect(RectInt(0, 16, 32, 48));
    rastercircle.SetCenter(rastercircle.GetSubRect().GetWidth()/2,
                           rastercircle.GetSubRect().GetHeight()/2);
    rastercircle.SetPosition(Window.GetWidth()/4, center.y);
    ////////////////////////////////////////////////////////////////////////////

    vectorcircle = Shape::Circle(Window.GetWidth()*.75, center.y, 16, Color::Blue);


    scalevector = VectorFloat(1.01, 1.01);

    rastertitle.SetText("Raster Vs. Vector Graphics");
}

RasterVsVectorState::~RasterVsVectorState()
{
    logger.log("Exiting Raster Vs. Vector state.");
}

void RasterVsVectorState::input()
{
    while (Window.GetEvent(event)) {
        if (event.Type == sf::Event::KeyPressed) {
            switch (event.Key.Code) {
                case sf::Key::O: setNextState(StateName::SCALARS_VS_VECTORS); return;
                case sf::Key::P: setNextState(StateName::MATRICES); return;
            }
        }
    }


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
    vectorcircle = Shape::Circle(2*Window.GetWidth()/3, center.y,
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

#endif // RASTERVSVECTORSTATE_H
