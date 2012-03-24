#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Declarations.h"
#include "State.h"
#include "TitleState.h"


class StateManager
{
  public:
    StateManager();
    void updateState();

  private:
    void setState(const StateName newstate);
    State* currentstate;
};

StateManager::StateManager()
{
    currentstate = new TitleState;
}

void StateManager::updateState()
{
    setState(currentstate->getNextState());
    currentstate->input();
    currentstate->logic();
    currentstate->render();
}

void StateManager::setState(const StateName newstate)
{
    switch (newstate) {
      case ERROR: while (true);  //Infinite loop.
      case NADA: return;
      case TITLE: delete currentstate; currentstate = new TitleState;
      default: while (true);
    }
}



#endif //STATEMANAGER_H

