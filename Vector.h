#ifndef VECTOR_H  //bytehis way, no file is accidentally included twice.
#define VECTOR_H  //Else the binary would needlessly expand.

/*Can be taken from a matrix or instatiated separately.*/

class Vector
{
  public:
    Vector() { set(0, 0); }
    Vector(const int newx, const int newy) { set(newx, newy); }
    Vector(const Vector& newvec) { set(newvec.x, newvec.y); }
    int x;
    int y;

    ///////////////////////////////////////////////////////////////
    //These are overloaded operators.  Built-in data types can
    //operated on, but user-made classes need to have them defined.
    //Not just for math, for instance "+" is useful for adding
    //text to strings.
    
    //"+=" adds to the left value.  "x += 2" = "x = x + 2"
    Vector& operator+=(const Vector& other)  
    { x += other.x; y += other.y; return *this; }
     
    Vector operator+(const Vector& other) const
    { return Vector(x + other.x, y + other.y); }
    
    //Likewise for other operators
    Vector& operator-=(const Vector& other)  
    { x -= other.x; y -= other.y; return *this; }
    
    Vector operator-(const Vector& other) const
    { return Vector(x - other.x, y - other.y); }
    
    Vector& operator*=(const byte other)
    { x *= other; y *= other; return *this; }
    
    Vector operator*(const byte other) const
    { return Vector(x * other, y * other); }
    
    byte operator*(const Vector& other)  const //Dot product
    { return x * other.x + y * other.y; }
    
    Vector& operator/=(const int other)
    { x /= other; y /= other; return *this; }
    
    Vector operator/(const int other) const
    { return Vector(x/other, y/other); }
    
    boolean operator==(const Vector& other) const
    { return (x == other.x && y == other.y); }
    
    boolean operator!=(const Vector& other) const
    { return !(operator==(other)); }
    /////////////////////////////////////////////////////////////
    
    
    //Distance to another vector
    float distanceTo(const Vector& other) const
    { return Vector(*this - other).length(); }
    
    //Gets a copy of this vector with the same direction, but length 1
    Vector getNormalized() const
    { float temp = length(); return Vector(x/temp, y/temp); }
    
    //So I can use the fast inverse square algorithm.  Can't just divide by 1 else the speed would be negated.
    /*
     * This very fast algorithm returns inverse square root of a number.
     * Its origin is not known, but it is believed to have been
     * developed by Silicon Graphics in the early 90's.  Well-known
     * for being used in the video game Quake III Arena.
     * 
     * http://tinyurl.com/cv4csc
     */
    float inverseLength() const
    {
      const int num = x*x + y*y;
      float z = num;
      long i = * ( long * ) &z;
      i = 0x5f3759df - ( i >> 1 );               
      z = * ( float * ) &i;
      return z *= ( 1.5F - ( num * 0.5F * z * z ) );
    }
    
    //Gets this vector's length.
    float length() const
    { return sqrt(x*x + y*y); }  
    
    //Sets this vector's length to 1
    void normalize() 
    { *this /= length(); } 
    
    //Sets this vector's values.
    void set(const byte newx, const byte newy)
    { x = newx; y = newy; }  
};

#endif //VECTOR_H

