#ifndef STATE_H
#define STATE_H

#include "Declarations.h"

//An abstract class that all states derive from.  All states have these methods
//and members in common.
class State
{
  public:
    State();
    virtual ~State() {}

    //Returns nextstate below; nextstate is set by any subclasses
    StateName getNextState() const;

    //Handles input; first third of the game loop
    virtual void input() = 0;

    //Does something after the input; second third
    virtual void logic() = 0;

    //Renders everything; last third
    virtual void render() = 0;

  protected:
    //Meant to be used in input(); checks whether we pressed O or P
    void checkForNextState(const StateName prev, const StateName next);

    //Sets the next state.  Only to be used inside subclasses.
    void setNextState(const StateName newnextstate);

    //The next state we're going for.
    StateName nextstate;
};
#endif //STATE_H
