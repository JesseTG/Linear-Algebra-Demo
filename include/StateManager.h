#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#define RESET currentstate.reset  //Cut down on text


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
#include "states/RotationState/RotationState.h"
#include "states/ScalingState/ScalingState.h"

//Owns the active state and manages its lifetime.
class StateManager
{
  public:
    StateManager();

    //Runs the game loop
    void updateState();

  private:
    //Resets currentstate with a new state
    void setState(const StateName newstate);

    //The pointer to the current state (relies on polymorphism)
    std::unique_ptr<State> currentstate;

    //If true, we're in fullscreen mode
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

    //Checks to see if the user exited the program
    if (INPUT.IsKeyDown(sf::Key::Escape)) {
        exit(EXIT_SUCCESS);
    }
    else if (INPUT.IsKeyDown(sf::Key::F4)) {  //Toggles full-screen mode
        Window.Create(VideoMode(640, 480, 32), "Linear Algebra Demo",
                      sf::Style::Titlebar | sf::Style::Close |
                      (sf::Style::Fullscreen * (isfullscreen = !isfullscreen)));
    } else if (INPUT.IsKeyDown(sf::Key::F1)) {
        Window.Capture().SaveToFile("screenshot.png");
    }
}

void StateManager::setState(const StateName newstate)
{
    //Creates whatever state matches with the enum class  //////////////////////
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
      case StateName::ROTATION: RESET(new RotationState); return;
      case StateName::SCALING: RESET(new ScalingState); return;
      default: throw std::runtime_error("Improper state!  Abort!");
    }
    ////////////////////////////////////////////////////////////////////////////
}



#endif //STATEMANAGER_H

