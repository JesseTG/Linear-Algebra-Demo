#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <SFML/Graphics.hpp>

class StateManager;
class State;
class TitleState;

enum class StateName {
  ERROR = -1,
  NADA = NULL,  //Remember that NULL = 0
  TITLE = 1,
  VECTORS,
  VECTORS_VS_SCALARS,
  RASTER_VS_VECTOR,
  MATRICES,
  TRANSLATION_DISTANCE_LENGTH,
  DOT_CROSS_PRODUCTS,
  REFLECTION,
  ROTATION,
  BAD_ROTATION,
  SHEARING,
  SCALING,
  PROJECTION,
  CONCLUSION
};

#endif //DECLARATIONS_H
