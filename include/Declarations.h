#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <SPI/SPI.h>
#include <Gameduino/GD.h>
#include <Gameduino/font8x8.h>
#include <IRremote/IRremote.h>

class NumMatrix;
class Shape;
class State;
class StateManager;
class Vector;
class TitleState;

//There are just shapes, but typedef'd for my convenience.
typedef Shape Cross;
typedef Shape Line;
typedef Shape Rect;
typedef Shape Triangle;

enum StateName {
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

//I'm not sure why I need these weird declarations, but apparently I do for AVR
//hardware (what the Arduino runs on).  ////////////////////////////////////////
extern "C" void __cxa_pure_virtual(void);
__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);
////////////////////////////////////////////////////////////////////////////////

#endif //DECLARATIONS_H
