#ifndef SHAPE_H
#define SHAPE_H

#include "Declarations.h"
#include "Plotter.h"


class Shape
{


    public:
        Shape(const byte newnumofvertices);
        ~Shape();

        void draw() const;

        void setVertice(const byte vertice, const Vector& newpos);

        void rotateBy(const int16_t theangle);

        void shearBy(const Vector& offset);

        void shearTo(const Vector& offset);

        void scaleBy(const Vector& offset);

        void moveBy(const Vector& newpos);

        //Transforms all points in this Shape by this matrix.
        void transform(const NumMatrix& offset);

        uint16_t getColor() const;

        void setColor(const byte r, const byte g, const byte b);

        void* operator new(size_t size) { return malloc(size); }
        void operator delete(void* obj) { free(obj); }

    private:
        Shape() {}
        NumMatrix* vertices;
        uint16_t color;
        int16_t angle;
        byte numofvertices;
};

Shape::Shape(const byte newnumofvertices)
{
    color = RGB(255, 255, 255);
    angle = 0;
    numofvertices = newnumofvertices;
    vertices = new NumMatrix[numofvertices];
}

Shape::~Shape()
{
    delete[] vertices;
}

void Shape::draw() const
{
    for (byte i = 0; i < numofvertices; ++i) {
        Vector temp1 = vertices[i % numofvertices].getTransformedVector();
        Vector temp2 = vertices[(i+1) % numofvertices].getTransformedVector();
        Plotter.line(temp1.x, temp1.y, temp2.x, temp2.y);
        //So we don't copy temps twice each.
    }
}

void Shape::setVertice(const byte vertice, const Vector& newpos)
{
    vertices[vertice](0, 2) = newpos.x;
    vertices[vertice](1, 2) = newpos.y;
}

void Shape::scaleBy(const Vector& offset) {
    for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 0) *= offset.x;
        vertices[i](1, 1) *= offset.y;
    }
}

void Shape::moveBy(const Vector& newpos)
{
    for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 2) += newpos.x;
        vertices[i](1, 2) += newpos.y;
    }
}

void Shape::transform(const NumMatrix& offset)
{
    for (byte i = 0; i < numofvertices; ++i) vertices[i] *= offset;
}

uint16_t Shape::getColor() const
{
    return color;
}

void Shape::setColor(const byte r, const byte g, const byte b)
{
    color = RGB(r, g, b);
}

#endif //SHAPE_H
