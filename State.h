#ifndef STATE_H
#define STATE_H

#include "Declarations.h"
#include "StateManager.h"



class State
{
  protected:
    StateName nextstate;
    
  public:
    virtual ~State() {};
    
    StateName getNextState() const { return this->nextstate; }
    void setNextState(const StateName newnextstate) { this->nextstate = newnextstate; }
      
    virtual void input() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    
};

#endif //STATE_H
