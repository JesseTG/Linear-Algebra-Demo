#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"
#include "Declarations.h"

class StateManager
{
  public:
  
    StateManager() { 
    }
  
    void setState(StateName newstate)
      { if (newstate != NADA) currentstate = newstate; }
      
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
