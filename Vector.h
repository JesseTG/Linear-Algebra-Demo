#ifndef VECTOR_H  //This way, no file is accidentally included twice.
#define VECTOR_H  //Else the binary would needlessly expand.

/*Can be taken from a matrix or instatiated separately.*/

template<class T>  //This is a template class.  That means I can use any data type
class Vector       //that has the below operators defined.
{
  public:
    Vector<T>() { set(0, 0); }
    Vector<T>(const T newx, const T newy) { set(newx, newy); }
    Vector<T>(const Vector<T>& newvec) { set(newvec.x, newvec.y); }
    T x;
    T y;

    ///////////////////////////////////////////////////////////////
    //These are overloaded operators.  Built-in data types can
    //operated on, but user-made classes need to have them defined.
    //Not just for math, for instance "+" is useful for adding
    //text to strings.
    
    //"+=" adds to the left value.  "x += 2" = "x = x + 2"
    Vector<T>& operator+=(const Vector<T>& other)  
    { x += other.x; y += other.y; return *this; }
     
    Vector<T> operator+(const Vector<T>& other)
    { return Vector<T>(x + other.x, y + other.y); }
    
    //Likewise for other operators
    Vector<T>& operator-=(const Vector<T>& other)  
    { x -= other.x; y -= other.y; return *this; }
    
    Vector<T> operator-(const Vector<T>& other)
    { return Vector<T>(x - other.x, y - other.y); }
    
    Vector<T>& operator*=(const T other)
    { x *= other; y *= other; return *this; }
    
    Vector<T> operator*(const T other)
    { return Vector<T>(x * other, y * other); }
    
    T operator*(const Vector<T>& other)  //Dot product
    { return x * other.x + y * other.y; }
    
    Vector<T>& operator/=(const T other)
    { x /= other; y /= other; return *this; }
    
    Vector<T> operator/(const T other)
    { return x/other.x + y/other.y; }
    
    boolean operator==(const Vector<T>& other)
    { return (x == other.x && y == other.y); }
    
    boolean operator!=(const Vector<T>& other)
    { return !(this == other); }
    /////////////////////////////////////////////////////////////
    
    
    //Distance to another vector
    Vector<T> distanceTo(const Vector<T>& other) const
    { return Vector<T>(this - other).length(); }
    
    //Gets a copy of this vector with the same direction, but length 1
    Vector<T> getNormalized() const
    { float temp = length(); return Vector<T>(x/temp, y/temp); }
    
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
    void set(const T newx, const T newy)
    { x = newx; y = newy; }  
    
    


};

#endif //VECTOR_H

