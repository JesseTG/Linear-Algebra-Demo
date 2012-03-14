#ifndef VECTOR_H
#define VECTOR_H

/*Can be taken from a matrix or instatiated separately.*/

template<class T>
class Vector 
{
public:
	Vector<T>(const T newx, const T newy)
            {set(newx, newy);}
        
        T x;
	T y;
        
        Vector<T>& operator+(const Vector<T>& other);
            
	void set(const T newx, const T newy);
            { x = newx; y = newy;}
            
	float length();
        float inverseLength();  //So I can use the fast inverse square algorithm.
	Vector<T> getNormalized();
	void normalize();
	Vector<int16_t> distanceTo(const Vector<int16_t>& other);

	Vector<T> crossProduct(Vector<T> vec1, Vector<T> vec2);
	Vector<T> dotProduct(Vector<T> vec1, Vector<T> vec2);
	
	
};

template<class T>
void Vector<T>::normalize()
{
  x /= length();
  y /= length();
}

template<class T>
void Vector<T>::getNormalized()
{
  return Vector<T>(x/length(), y/length());
}


template<class T>
Vector<T>& Vector<T>::operator+(const Vector<T>& other)
{
  x += other.x;
  y += other.y;
  return *this;
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
