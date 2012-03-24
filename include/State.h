#ifndef STATE_H
#define STATE_H

#include "Declarations.h"
#include <Gameduino/GD.h>

class State
{


  public:
    virtual ~State() {};

    StateName getNextState() const;
    void setNextState(const StateName newnextstate);

    uint16_t getColor() const;
    void setColor(const byte r, const byte g, const byte b);

    void* operator new(size_t size) { return malloc(size); }
    void operator delete(void *obj) { free(obj); }

    virtual void input() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;

  protected:
    StateName nextstate;

  private:
    uint16_t linecolor;

};

StateName State::getNextState() const
{ return this->nextstate; }

void State::setNextState(const StateName newnextstate)
{ this->nextstate = newnextstate; }

uint16_t State::getColor() const
{ return linecolor; }

void State::setColor(const byte r, const byte g, const byte b)
{ linecolor = RGB(r, g, b); }


#endif //STATE_H
