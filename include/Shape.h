#ifndef SHAPE_H
#define SHAPE_H

#include "Declarations.h"
#include "etc/Plotter.h"

#include <math.h>

/*
 * Here we use a lot of simplified matrix multiplication for the sake of
 * saving computation time, thus improving speed.  Essentially, we multiply only
 * two or three numbers at a time rather than a whole matrix.  This is the sort
 * of thing we do all the time in "baby algebra", except this time it's for more
 * than our own convenience.
 */


class Shape
{
    public:
        Shape() {}
        Shape(const byte newnumofvertices);
        ~Shape();

        //Rotates with an unoptimized method to prove my point.
        void badRotateBy(int16_t theangle);

        //Displays this shape on-screen.  Not supposed to be called until AFTER
        //all the logic has been done (shape transformations, etc.)
        void draw() const;

        //Moves the entire shape this far.  First vertice is the reference,
        void moveBy(const Vector& newpos);

        //Rotates the entire shape.
        void rotateBy(int16_t theangle);

        //Scales this shape by this much.
        void scaleBy(const Vector& offset);

        //Sets the amount of vertices that this shape has due to C++ rules
        void setNumOfVertices(const byte newnumofvertices);

        //Sets a specfic vertice's location.  Meant to be for initialization.
        void setVertice(const byte vertice, const Vector& newpos);

        //Shears this shape's points by this much.  Both x and y can be used.
        void shearBy(const Vector& offset);

        //Transforms all points in this Shape by this matrix.
        void transform(const NumMatrix& offset);

        //Allocates memory for this shape.
        void* operator new(size_t size) { return malloc(size); }

        //Frees the memory this shape holds, essentially deleting the shape.
        //Not entirely necessary since there's no operating system that wants it
        //back, but still nice to have.
        void operator delete(void* obj) { free(obj); }

        //Gets a rotation matrix.  Trigonometric functions are only used twice,
        //which is good since they're computationally expensive!
        static NumMatrix getRotationMatrix(const int16_t newangle);

    private:
        //A pointer to all the matrices; we don't know until runtime how many
        //vertices a shape will need.
        NumMatrix* vertices;

        //The amount of vertices this shape has, since we can't access an
        //array's size in C++.
        byte numofvertices;
};

Shape::Shape(const byte newnumofvertices)
{
    numofvertices = newnumofvertices;
    vertices = new NumMatrix[numofvertices];
}

Shape::~Shape()
{
    delete[] vertices;
}

void Shape::badRotateBy(int16_t theangle)
{
    theangle *= (PI/180);
    //I can't simulate novice rotation EXACTLY since I'm storing coordinates
    //in matrices, not vectors.  But this is close enough.
    for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 0) *= cos(theangle);
        vertices[i](0, 1) *= -sin(theangle);
        vertices[i](1, 0) *= sin(theangle);
        vertices[i](1, 1) *= cos(theangle);
    }
}

void Shape::draw() const
{
    for (byte i = 0; i < numofvertices; ++i) {
        Vector temp1 = vertices[i % numofvertices].getTransformedVector();
        Vector temp2 = vertices[(i+1) % numofvertices].getTransformedVector();
        Plotter.line(temp1.x, temp1.y, temp2.x, temp2.y);
        //So we don't make temps twice each.
    }
}

void Shape::moveBy(const Vector& newpos)
{
    //This is just adding coordinates to the matrix.
    for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 2) += newpos.x;
        vertices[i](1, 2) += newpos.y;
    }
}

void Shape::rotateBy(const int16_t newangle)
{
    NumMatrix rot = Shape::getRotationMatrix(newangle);
    for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 0) *= rot(0, 0);
        vertices[i](0, 1) *= rot(0, 1);
        vertices[i](1, 0) *= rot(1, 0);
        vertices[i](1, 1) *= rot(1, 1);
    }
}

void Shape::shearBy(const Vector& offset)
{
    for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 1) += offset.x;
        vertices[i](1, 0) += offset.y;
    }
}

void Shape::setNumOfVertices(const byte newnumofvertices)
{
    numofvertices = newnumofvertices;
}

void Shape::setVertice(const byte vertice, const Vector& newpos)
{
    vertices[vertice](0, 2) = newpos.x;
    vertices[vertice](1, 2) = newpos.y;
}

void Shape::scaleBy(const Vector& offset) {
    /* This is the 2x2 matrix you'd need (x and y are scaling factors).
     * [x 0]
     * [0 y]
     */
    for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 0) *= offset.x;
        vertices[i](1, 1) *= offset.y;
    }
}


void Shape::transform(const NumMatrix& offset)
{
    for (byte i = 0; i < numofvertices; ++i) vertices[i] *= offset;
}

NumMatrix Shape::getRotationMatrix(int16_t newangle)
{
    /*
     * This is the 2x2 matrix you'd need (x is an angle).
     * [ cos(x)   -sin(x) ]
     * [ sin(x)    cos(x) ]
     */
    newangle *= (PI/180);  //Convert to radians.
    NumMatrix temp;
    temp(0, 0) = cos(newangle);
    temp(0, 1) =  -sin(newangle);
    temp(1, 0) = -temp(0, 1);
    temp(1, 1) = temp(0, 0);
    temp(2, 2) = 1;

    return temp;
}

#endif //SHAPE_H
