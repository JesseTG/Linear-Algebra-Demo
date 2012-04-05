#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Declarations.h"
#include "State.h"
#include "states/TitleState.h"
#include "states/VectorState.h"
#include "states/ScalarVsVectorState.h"
#include "states/RasterVsVectorState.h"
#include "states/MatricesState.h"
#include "states/TranslationDistanceLengthState.h"

class StateManager
{
  public:
    StateManager();
    void updateState();

  private:
    void setState(const StateName newstate);
    std::shared_ptr<State> currentstate;
    bool isfullscreen;
};

StateManager::StateManager()
{
    currentstate.reset(new TitleState);
    isfullscreen = false;
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
    else if (Window.GetInput().IsKeyDown(sf::Key::F4)) {
        Window.Create(sf::VideoMode(640, 480, 32), "Linear Algebra Demo",
                      sf::Style::Titlebar | sf::Style::Close |
                      (sf::Style::Fullscreen * (isfullscreen = !isfullscreen)));
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
      case StateName::MATRICES: currentstate.reset(new MatricesState); return;
      case StateName::TRANSLATION_DISTANCE_LENGTH: currentstate.reset(new TranslationDistanceLengthState); return;
      default: throw std::runtime_error(logger.log("Improper state!  Abort!"));
    }

}



#endif //STATEMANAGER_H

