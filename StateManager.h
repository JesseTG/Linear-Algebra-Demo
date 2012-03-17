#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

class StateManager
{
  public:
    StateManager() { currentstate }
  
    void setState(StateName newstate)
      { if (newstate == NADA) return; else currentstate = newstate; }
      
    void updateState() {
      setState(currentstate->getNextState());
      currentstate->input();
      currentstate->logic();
      currentstate->render();
    }
    
  private:
    State* currentstate;
};

#endif //STATEMANAGER_H
