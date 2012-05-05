#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#define RESET(a) currentstate.reset(a); return;  //Cut down on text

#include "Declarations.h"
#include "State.h"
#include "states/TitleState.h"
#include "states/VectorState.h"
#include "states/ScalarVsVectorState.h"
#include "states/RasterVsVectorState.h"
#include "states/MatricesState.h"
#include "states/TranslationDistanceLengthState.h"
#include "states/DotProductState.h"
#include "states/RotationState.h"
#include "states/duckhunt/DuckHuntTitle.h"
#include "states/duckhunt/DuckHuntGameState.h"

constexpr uint_fast8_t normalstyle = sf::Style::Titlebar | sf::Style::Close;

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
                      normalstyle | (sf::Style::Fullscreen * (isfullscreen = !isfullscreen)));
    } else if (INPUT.IsKeyDown(sf::Key::F1)) {
        Window.Capture().SaveToFile("screenshot.png");
    }
}

void StateManager::setState(const StateName newstate)
{
    //Creates whatever state matches with the enum class  //////////////////////
    switch (newstate) {
      case StateName::NADA              : return;
      case StateName::TITLE             : RESET(new TitleState                    );
      case StateName::VECTORS           : RESET(new VectorState                   );
      case StateName::SCALARS_VS_VECTORS: RESET(new ScalarVsVectorState           );
      case StateName::RASTER_VS_VECTOR  : RESET(new RasterVsVectorState           );
      case StateName::MATRICES          : RESET(new MatricesState                 );
      case StateName::TRANSLATION       : RESET(new TranslationDistanceLengthState);
      case StateName::DOT_PRODUCTS      : RESET(new DotProductState               );
      case StateName::ROTATION          : RESET(new RotationState                 );
      case StateName::DUCKHUNT_TITLE    : RESET(new DuckHuntTitle                 );
      case StateName::DUCKHUNT_GAME     : RESET(new DuckHuntGameState             );
      default: throw std::runtime_error("Improper state " + boost::lexical_cast<std::string, int>(int(newstate)) + "!  Abort!");
    }
    ////////////////////////////////////////////////////////////////////////////
}



#endif //STATEMANAGER_H

