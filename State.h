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
    virtual void render() = 0;
    
  protected:
    StateName nextstate;
    
};

StateName State::getNextState() const
{ return this->nextstate; }

void State::setNextState(const StateName newnextstate)
{ this->nextstate = newnextstate; }
 

#endif //STATE_H
