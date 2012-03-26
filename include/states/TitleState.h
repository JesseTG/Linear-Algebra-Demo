#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "../Declarations.h"
#include "../State.h"

/*
 * This is my project's title screen.  It features only a rotating cross and
 * some information off to the sides.  (I don't have much room for text anyway.)
 */

#define ANGLE 1  //The angle the cross rotates each frame.

class TitleState : public State
{
  public:
    TitleState();
    ~TitleState();


    void input();
    void logic();
    void render();

    void* operator new(size_t size) { return malloc(size); }
    void operator delete(void *obj) { free(obj); }

  private:
    //The cross that will be spinning on the title screen
    Cross cross;

    //The rotation matrix that we'll use to spin the cross, since the cross will
    //be spinning at a constant rate.
    NumMatrix rotationmatrix;
};

TitleState::TitleState()
{
    //Initialize rotationmatrix so we can cut down on the trigonometry.
    rotationmatrix = Shape::getRotationMatrix(1);

    //This is white.  Remember, only one color!
    setColor(255, 255, 255);

    //NADA means next frame we stay in this state, or we'd never see this one!
    setNextState(NADA);

    //Initialize cross and the location of each of its vertices.  //////////////
    cross.setNumOfVertices(12);
    cross.setVertice(0, Vector(80, 40));
    cross.setVertice(1, Vector(168, 40));
    cross.setVertice(2, Vector(168, 88));
    cross.setVertice(3, Vector(216, 88));
    cross.setVertice(4, Vector(216, 168));
    cross.setVertice(5, Vector(168, 168));
    cross.setVertice(6, Vector(168, 216));
    cross.setVertice(7, Vector(88, 216));
    cross.setVertice(8, Vector(88, 168));
    cross.setVertice(9, Vector(40, 168));
    cross.setVertice(10, Vector(40, 88));
    cross.setVertice(11, Vector(88, 88));
    ////////////////////////////////////////////////////////////////////////////
}

TitleState::~TitleState()
{

}

void TitleState::input()
{
    //TODO: Work on getting input!  Need to get familiar IRrecv's API again.
    if (/* user presses a certain button */) setNextState(/* state 2*/);
}

void TitleState::logic()
{
    cross.transform(rotationmatrix);

}

void TitleState::render()
{
    cross.draw();
}

#endif //TITLESTATE_H
