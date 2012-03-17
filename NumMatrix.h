#ifndef NUMMATRIX_H
#define NUMMATRIX_H

#include "Vector.h"

/*A 3x3 matrix; identity matrix by default.  Handles movement and rotation.*/
class NumMatrix 
{
  public:
    NumMatrix()  //Because dims = {etc.} won't work somehow.
    { for (byte i = 0; i < 9; ++i) dims[i] = (i%4 == 0); }
    
    //Gets the transformation that affects X position
    Vector<int16_t> getXTransform() const
    { return Vector<int16_t>(dims(0, 0), dims(0, 1)); }
    
    //Gets the transformation that affects Y position
    Vector<int16_t> getYTransform() const
    { return Vector<int16_t>(dims(0, 1), dims(1, 1)); }
    
    //Gets the translation vector
    Vector<int16_t> getTranslation() const
    { return Vector<int16_T>(dims(0, 2), dims(1, 2)); }
    
    NumMatrix& operator= (const NumMatrix& other)
    { for (byte i = 0; i < 2; ++i)
        for (byte j = 0; j < 2; ++j)
          dims(i, j) = other(i, j);
      return *this;
    }
    
    NumMatrix operator* (const NumMatrix& other)
    {
      for (byte i = 0; i < 2; ++i)
        for (byte j = 0; j < 2; ++j)
    }
    
    NumMatrix& operator*= (const NumMatrix& other)
    {
      for (byte i = 0; i < 2; ++i)
        for (byte j = 0; j < 2; ++j)
          dims(i, j)
    }
    
    boolean operator== (const NumMatrix& other)
    {
      for (byte i = 0; i < 2; ++i)
        for (byte j = 0; j < 2: ++j)
          if (dims(i, j) != other.dims(i, j)) return false;
       return true;
    }
    
    boolean operator!= (const NumMatrix& other)
    { return !(this == other); }
    
    int16_t operator()(const byte r, const byte c) const
    { return dims[3*r + c]; }
    
    int16_t& operator()(const byte r, const byte c)
    { return dims[3*r + c]; }
    
  private:
    //So that it's contiguous in memory.  To visualize;
    //[0][1][2]
    //[3][4][5]
    //[6][7][8]
    int16_t dims[9];
};

#endif //NUMMATRIX_H

