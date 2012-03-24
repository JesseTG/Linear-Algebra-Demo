#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "Declarations.h"
#include "State.h"


class TitleState : public State
{
  public:
    TitleState();
    ~TitleState();
    void* operator new(size_t size) { return malloc(size); }
    void operator delete(void *obj) { free(obj); }

    void input();
    void logic();
    void render();
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
