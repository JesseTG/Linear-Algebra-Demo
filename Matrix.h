#ifndef MATRIX_H
#define MATRIX_H

/*A 3x3 matrix; identity matrix by default.  Handles movement and rotation.*/
class Matrix 
{
    public:
	Matrix ();
	Vector<int16_t> getXVector ();
	Vector<int16_t> getYVector ();
	Vector<int16_t> getTranslationVector ();
	Matrix& operator= (const Matrix& other);
	Matrix operator+ (const Matrix& other);
	Matrix& operator+= (const Matrix& other);
	Matrix operator- (const Matrix& other);
	Matrix& operator-= (const Matrix& other);
	Matrix operator* (const Matrix& other);
	Matrix& operator*= (const Matrix& other);
	bool operator== (const Matrix& other);
	bool operator!= (const Matrix& other);
	int16_t operator() (const byte row,
	                    const byte col);
	int16_t& operator() (const byte row,
	                     const byte col);
    private:
	int16_t dimensions[3][3];
};

#endif //MATRIX_H
