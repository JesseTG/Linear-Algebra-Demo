#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "bgtile.h"
#include "Plotter.h"
#include "Vector.h"
#include "NumMatrix.h"

enum StateName { 
  ERROR = -2, NADA = -1, INTRO = 0,
};

/*
 * This algorithm returns inverse square root of a number.
 * It's highly optimized.  Its origin is not known, but it is
 * believed to have been developed by Silicon Graphics in
 * the early 90's.  Well-known for being used in the video
 * game Quake III Arena.
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

