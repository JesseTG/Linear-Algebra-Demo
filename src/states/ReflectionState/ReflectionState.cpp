#include "../../../include/states/ReflectionState/ReflectionState.h"

ReflectionState::ReflectionState()
{
    opaopa.reset(new OpaOpa);
}

ReflectionState::~ReflectionState()
{
    //dtor
}

void ReflectionState::input()
{
    checkForNextState(StateName::DOT_PRODUCTS, StateName::NADA);
}

void ReflectionState::logic()
{
    opaopa->move();
}

void ReflectionState::render() const
{
    Window.Draw(bg);
    Window.Draw(opaopa->getSprite());
    Window.Display();
}
