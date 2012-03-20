#include <SPI.h>
#include <GD.h>

class NumMatrix;
class Shape;
class State;
class StateManager;
class Vector;

class TitleState;

#include "NumMatrix.h"
#include "Shape.h"
#include "State.h"
#include "StateManager.h"
#include "TitleState.h"
#include "Vector.h"

#include "bgtile.h"
#include "Plotter.h"



#ifndef ENUM_DEFINED
#define ENUM_DEFINED
typedef enum { 
  ERROR = -2,
  NADA = -1,
  TITLE = 0,
  INTRO,
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
} StateName;
#endif
