#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#define RESET currentstate.reset

#include "Declarations.h"
#include "State.h"
#include "states/TitleState.h"
#include "states/VectorState.h"
#include "states/ScalarVsVectorState.h"
#include "states/RasterVsVectorState.h"
#include "states/MatricesState.h"
#include "states/TranslationDistanceLengthState/TranslationDistanceLengthState.h"
#include "states/DotProductState.h"
#include "states/ReflectionState/ReflectionState.h"

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
    RESET(new TitleState);
    isfullscreen = false;
}

void StateManager::updateState()
{
    setState(currentstate->getNextState());
    currentstate->input();
    currentstate->logic();
    currentstate->render();

    if (INPUT.IsKeyDown(sf::Key::Escape)) {
        exit(EXIT_SUCCESS);
    }
    else if (INPUT.IsKeyDown(sf::Key::F4)) {
        Window.Create(sf::VideoMode(640, 480, 32), "Linear Algebra Demo",
                      sf::Style::Titlebar | sf::Style::Close |
                      (sf::Style::Fullscreen * (isfullscreen = !isfullscreen)));
    }
}

void StateManager::setState(const StateName newstate)
{
    switch (newstate) {
      case StateName::NADA: return;
      case StateName::TITLE: RESET(new TitleState); return;
      case StateName::VECTORS: RESET(new VectorState); return;
      case StateName::SCALARS_VS_VECTORS: RESET(new ScalarVsVectorState); return;
      case StateName::RASTER_VS_VECTOR: RESET(new RasterVsVectorState); return;
      case StateName::MATRICES: RESET(new MatricesState); return;
      case StateName::TRANSLATION_DISTANCE_LENGTH: RESET(new TranslationDistanceLengthState); return;
      case StateName::DOT_PRODUCTS: RESET(new DotProductState); return;
      case StateName::REFLECTION: RESET(new ReflectionState); return;
      default: throw std::runtime_error("Improper state!  Abort!");
    }

}



#endif //STATEMANAGER_H

