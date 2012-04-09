#ifndef STATE_H
#define STATE_H

#include "Declarations.h"

class State
{
  public:
    virtual ~State() {};

    StateName getNextState() const;
    void setNextState(const StateName newnextstate);

    virtual void input() = 0;
    virtual void logic() = 0;
    virtual void render() const = 0;

  protected:
    StateName nextstate;
};
#endif //STATE_H
