#ifndef NUMMATRIX_H
#define NUMMATRIX_H

#include "Vector.h"

/*A 3x3 matrix; identity matrix by default.  Handles movement and rotation.*/
class NumMatrix
{
  public:
    NumMatrix()  //This generates a blank matrix.
    { for (byte i = 0; i < 9; ++i) dims[i] = 0; }

    //Gets the transformation that affects X position
    Vector getXTransform() const
    { return Vector(get(0,0), get(0, 1)); }

    //Gets the transformation that affects Y position
    Vector getYTransform() const
    { return Vector(get(1, 0), get(1, 1)); }

    //Gets the translation vector
    Vector getTranslation() const
    { return Vector(get(0, 2), get(1, 2)); }

    //Gets the translation vector with both transformation vectors applied
    Vector getTransformedVector() const
    {
      return Vector(get(0,0) * get(0,2) + get(0,1) * get(1,2),
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
      for (byte i = 0; i < 3; ++i)
        for (byte j = 0; j < 3; ++j)
          for (byte k = 0; k < 3; ++k)
            temp(i, j) += this->operator()(i, k) * other(k, j);

      return temp;
    }

    //This will likely be used more often that operator*.
    NumMatrix& operator*=(const NumMatrix& other)
    {
      for (byte i = 0; i < 3; ++i)
        for (byte j = 0; j < 3; ++j)
          for (byte k = 0; k < 3; ++k)
            this->operator()(i, k) *= other(k, j);

      return *this;
    }

    boolean operator==(const NumMatrix& other)
    {
      for (byte i = 0; i < 9; ++i)
          if (dims[i] != other[i]) return false;
      return true;
    }

    boolean operator!=(const NumMatrix& other)
    { return !(operator==(other)); }

    float operator()(const byte r, const byte c) const
    { return get(r, c); }

    float& operator()(const byte r, const byte c)
    { return dims[3*r + c]; }

    //So we can refer to this NumMatrix by both one index and two.
    float operator[](const byte i) const
    { return get(i); }

    float& operator[](const byte i)
    { return dims[i]; }

    //And we have an explicit function, just in case we need one.
    float get(const byte r, const byte c) const
    { return dims[3*r + c]; }

    float get(const byte i) const
    { return dims[i]; }

    //Returns an identity matrix.
    static NumMatrix getIdentity()
    {
      NumMatrix temp;
      for (byte i = 0; i < 9; ++i) temp[i] = (i%4 == 0);
      return temp;
    }

    void* operator new(size_t size) { return malloc(size); }
    void* operator new[](size_t size) { return malloc(size); }

    void operator delete(void* obj) { free(obj); }
    void operator delete[](void* obj) { free(obj); }

  private:
    //So that it's contiguous in memory.  To visualize;
    //[0][1][2]
    //[3][4][5]
    //[6][7][8]
    float dims[9];
};

#endif //NUMMATRIX_H

