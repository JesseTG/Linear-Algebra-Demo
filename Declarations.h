#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "bgtile.h"
#include "Plotter.h"
#include "Vector.h"
#include "NumMatrix.h"
#include "Shape.h"


template <class T> class Vector;
template <byte numofvertices> class Shape;
class State;
class NumMatrix;
class StateManager;

enum StateName { 
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
};

/*
 * This very fast algorithm returns inverse square root of a number.
 * Its origin is not known, but it is believed to have been
 * developed by Silicon Graphics in the early 90's.  Well-known
 * for being used in the video game Quake III Arena.
 * 
 * http://tinyurl.com/cv4csc
 */
float fastInvertSquare(const float num)
{
  float y  = num;
  long i  = * ( long * ) &y;
  i  = 0x5f3759df - ( i >> 1 );               
  y  = * ( float * ) &i;
  return y *= ( 1.5F - ( num * 0.5F * y * y ) );
}

#endif //DECLARATIONS_H

