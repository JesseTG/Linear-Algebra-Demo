#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Declarations.h"
#include "State.h"
#include "states/TitleState.h"
#include "states/VectorState.h"
#include "states/ScalarVsVectorState.h"
#include "states/RasterVsVectorState.h"

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

    if (Window.GetInput().IsKeyDown(sf::Key::Escape)) {
        logger.log("Program ended normally.");
        exit(EXIT_SUCCESS);
    }
}

void StateManager::setState(const StateName newstate)
{
    switch (newstate) {
      case StateName::NADA: return;
      case StateName::TITLE: currentstate.reset(new TitleState); return;
      case StateName::VECTORS: currentstate.reset(new VectorState); return;
      case StateName::SCALARS_VS_VECTORS: currentstate.reset(new ScalarVsVectorState); return;
      case StateName::RASTER_VS_VECTOR: currentstate.reset(new RasterVsVectorState); return;
      default: throw std::runtime_error(logger.log("Improper state!  Abort!"));
    }
}



#endif //STATEMANAGER_H

