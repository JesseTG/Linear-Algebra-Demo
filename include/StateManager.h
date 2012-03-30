#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Declarations.h"
#include "State.h"
#include "states/TitleState.h"
#include "states/VectorState.h"


enum class StateName : char;

class StateManager
{
  public:
    StateManager();
    void updateState();

  private:
    void setState(const StateName newstate);
    std::shared_ptr<State> currentstate;
};

StateManager::StateManager()
{
    currentstate.reset(new TitleState);
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
      case StateName::NADA: return;
      case StateName::TITLE: currentstate.reset(new TitleState); return;
      case StateName::VECTORS: currentstate.reset(new VectorState); return;
      default: throw std::runtime_error("Improper state!  Abort!"); return;
    }
}



#endif //STATEMANAGER_H

