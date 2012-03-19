#ifndef VECbyteOR_H  //bytehis way, no file is accidentally included twice.
#define VECbyteOR_H  //Else the binary would needlessly expand.

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
     
    Vector operator+(const Vector& other)
    { return Vector(x + other.x, y + other.y); }
    
    //Likewise for other operators
    Vector& operator-=(const Vector& other)  
    { x -= other.x; y -= other.y; return *this; }
    
    Vector operator-(const Vector& other)
    { return Vector(x - other.x, y - other.y); }
    
    Vector& operator*=(const byte other)
    { x *= other; y *= other; return *this; }
    
    Vector operator*(const byte other)
    { return Vector(x * other, y * other); }
    
    byte operator*(const Vector& other)  //Dot product
    { return x * other.x + y * other.y; }
    
    Vector& operator/=(const byte other)
    { x /= other; y /= other; return *this; }
    
    Vector operator/(const byte other)
    { return x/other.x + y/other.y; }
    
    boolean operator==(const Vector& other)
    { return (x == other.x && y == other.y); }
    
    boolean operator!=(const Vector& other)
    { return !(this == other); }
    /////////////////////////////////////////////////////////////
    
    
    //Distance to another vector
    Vector distanceTo(const Vector& other) const
    { return Vector(this - other).length(); }
    
    //Gets a copy of this vector with the same direction, but length 1
    Vector getNormalized() const
    { float temp = length(); return Vector(x/temp, y/temp); }
    
    //So I can use the fast inverse square algorithm.  Can't just divide by 1 else the speed would be negated.
    float inverseLength() const
    { return fastInvertSquare(x*x + y*y); }
    
    //Gets this vector's length.
    float length() const
    { return sqrt(x*x + y*y); }  
    
    //Sets this vector's length to 1
    void normalize() 
    { this /= length(); } 
    
    //Sets this vector's values.
    void set(const byte newx, const byte newy)
    { x = newx; y = newy; }  
};

#endif //VECbyteOR_H

