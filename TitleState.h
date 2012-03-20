#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "Declarations.h"
#include "State.h"


class TitleState : public State
{
  public:
    TitleState();
    virtual ~TitleState();
    
    virtual void input();
    virtual void logic();
    virtual void render();
};

TitleState::TitleState()
{
}

TitleState::~TitleState()
{
}

void TitleState::input()
{
}

void TitleState::logic()
{
}

void TitleState::render()
{
}

#endif //TITLESTATE_H
