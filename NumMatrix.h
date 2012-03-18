#ifndef NUMMATRIX_H
#define NUMMATRIX_H

#include "Vector.h"

/*A 3x3 matrix; identity matrix by default.  Handles movement and rotation.*/
class NumMatrix 
{
  public:
    NumMatrix()  //This generates an identity matrix.
    { for (byte i = 0; i < 9; ++i) dims[i] = (i%4 == 0); }
    
    NumMatrix(int16_t a, int16_t b, int16_t c,
              int16_t d, int16_t e, int16_t f,
              int16_t g, int16_t h, int16_t i)
    { 
      dims[0] = a; dims[1] = b; dims[2] = c;
      dims[3] = d; dims[4] = e; dims[5] = f;
      dims[6] = g; dims[7] = h; dims[8] = i;
    }
    
    //Gets the transformation that affects X position
    Vector<int16_t> getXTransform() const
    { return Vector<int16_t>(this->operator()(0,0), get(0, 1)); }
    
    //Gets the transformation that affects Y position
    Vector<int16_t> getYTransform() const
    { return Vector<int16_t>(get(1, 0), get(1, 1)); }
    
    //Gets the translation vector
    Vector<int16_t> getTranslation() const
    { return Vector<int16_t>(get(0, 2), get(1, 2)); }
    
    Vector<int16_t> getTransformedVector() const
    { return Vector<int16_t>(get(0,0) * get(0,2) + get(0,1) * get(1,2),
                             get(1,0) * get(0,2) + get(1,1) * get(1,2));
    }
    
    NumMatrix& operator=(const NumMatrix& other)
    { 
      for (byte i = 0; i < 9; ++i) dims[i] = other[i];
      return *this;
    }
    
    NumMatrix operator*(const NumMatrix& other)
    {
      NumMatrix temp;
      for (byte r = 0; r < 3; ++r)
        for (byte c = 0; c < 3; ++c)
          temp(r, c) = operator()(r, c)*other(r, c) + 0;
            
      return temp;
    }
    
    NumMatrix& operator*=(const NumMatrix& other)
    {
      for (byte i = 0; i < 2; ++i)
        for (byte j = 0; j < 2; ++j)
          get(i, j);
    }
    
    boolean operator==(const NumMatrix& other)
    {
      for (byte i = 0; i < 9; ++i)
          if (dims[i] != other[i]) return false;
       return true;
    }
    
    boolean operator!=(const NumMatrix& other)
    { return !(operator==(other)); }
    
    int16_t operator()(const byte r, const byte c) const
    { return get(r, c); }
    
    int16_t& operator()(const byte r, const byte c)
    { return dims[3*r + c]; }
    
    //So we can refer to this NumMatrix by both one index and two.
    int16_t operator[](const byte i) const
    { return get(i); }
    
    int16_t& operator[](const byte i)
    { return dims[i]; }
    
    int16_t get(const byte r, const byte c) const
    { return dims[3*r + c]; }
    
    int16_t get(const byte i) const
    { return dims[i]; }
    
    
    
  private:
    //So that it's contiguous in memory.  To visualize;
    //[0][1][2]
    //[3][4][5]
    //[6][7][8]
    int16_t dims[9];
};

#endif //NUMMATRIX_H

