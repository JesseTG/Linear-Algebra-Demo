#include "../include/State.h"

//I don't want to put these tiny methods in a separate file, but if I don't
//the linker gives me errors.
StateName State::getNextState() const
{ return this->nextstate; }

void State::setNextState(const StateName newnextstate)
{ this->nextstate = newnextstate; }
