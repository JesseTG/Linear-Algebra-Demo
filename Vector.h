#ifndef VECTOR_H
#define VECTOR_H

/*Can be taken from a matrix or instatiated separately.*/

template<class T>  //This is a template class.  That means I can use any data type
class Vector       //that has the below operators defined.
{
  public:
    Vector<T>() { set(0, 0); }
    Vector<T>(const T newx, const T newy) { set(newx, newy); }
    T x;
    T y;

    //These are overloaded operators.  Built-in data types can be
    //operated on, but user-made classes need to have them defined.
    //Not just for math, for instance "+" is useful for adding
    //text to strings.
    Vector<T>& operator+=(const Vector<T>& other);  //"+=" adds to the left value.  "x += 2" = "x = x + 2"
    Vector<T> operator+(const Vector<T>& other);
    Vector<T>& operator-=(const Vector<T>& other);  //Likewise for other operators
    Vector<T> operator-(const Vector<T>& other);
    Vector<T>& operator*=(const T other);
    Vector<T> operator*(const T other);
    T operator*(const Vector<T>& other);  //Dot product
    Vector<T>& operator/=(const T other);
    Vector<T> operator/(const T other);

    
    Vector<T> distanceTo(const Vector<T>& other) const;
    Vector<T> getNormalized() const;  //Gets a copy of this vector with the same direction, but length 1
    float inverseLength() const;  //So I can use the fast inverse square algorithm.  Can't just divide by 1 else the speed would be negated.
    float length() const;  //Gets this vector's length.
    void normalize();  //Sets this vector's length to 1
    Vector<T> getPerpendicular() const;  //In theory a cross product, though they're not directly useful in 2D.
    void set(const T newx, const T newy) { x = newx; y = newy; }  //Sets this vector's values.
    
    


};




template<class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other)
{
  x += other.x;
  y += other.y;
  return *this;
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& other)
{
  return Vector<T>(x + other.x, y + other.y);
}

template<class T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& other)
{
  return Vector<T>(x - other.x, y - other.y);
}

template<class T>
Vector<T>& Vector<T>::operator*=(const T other)
{
  x *= other;
  y *= other;
  return *this;
}

template<class T>
Vector<T> Vector<T>::operator*(const T other)
{
  return Vector<T>(x * other, y * other);
}

template<class T>
T Vector<T>::operator*(const Vector<T>& other)
{
  return x * other.x + y * other.y;
}

template<class T>
void Vector<T>::normalize()
{
  this /= length();
}

template<class T>
Vector<T> Vector<T>::getNormalized()
{
  return Vector<T>(x/length(), y/length());
}

template<class T>
float Vector<T>::length()
{
  return sqrt(x*x + y*y);
}

float Vector<T>::inverseLength()
{
  return fastInvertSquare(x*x + y*y);
}

#endif //VECTOR_H

