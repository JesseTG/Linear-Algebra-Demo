#ifndef SHAPE_H
#define SHAPE_H

#include <GD.h>
#include "Declarations.h"
#include "Plotter.h"


class Shape
{
  private:
    Shape() {}
    NumMatrix vertices[numofvertices];
    uint16_t color;
    int16_t angle;
    byte numofvertices;
    
  public:
  
    Shape(const byte newnumofvertices)
    {
      color = RGB(255, 255, 255);
      angle = 0;
      numofvertices = newnumofvertices;
      for (byte i = 0; i < numofvertices; ++i) vertices[i] = Vector(0, 0);
    }
      
    void draw() const
    {
      for (byte i = 0; i < numofvertices; ++i) {
        Vector temp1 = vertices[i%numofvertices].getTransformedVector();
        Vector temp2 = vertices[(i+1)%numofvertices].getTransformedVector();
        Plotter.line(temp1.x, temp1.y, temp2.x, temp2.y);  //So we don't copy temps twice
      }
    }
    
    void setVertice(const byte vertice, const Vector& newpos)
    { vertices[vertice](0, 2) = newpos.x; vertices[vertice](1, 2) = newpos.y; }
    
    void rotateBy(const int16_t theangle);
    
    void shearBy(const Vector& offset);
    
    void shearTo(const Vector& offset);
    
    void scaleBy(const Vector& offset)
    {
      for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 0) *= offset.x;
        vertices[i](1, 1) *= offset.y;
      }
    }
    
    void moveBy(const Vector& newpos)
    {
      for (byte i = 0; i < numofvertices; ++i) {
        vertices[i](0, 2) += newpos.x;
        vertices[i](1, 2) += newpos.y;
      }
    }
    
    //Transforms all points in this Shape by this matrix.
    void transform(const NumMatrix& offset)
    { for (byte i = 0; i < numofvertices; ++i) vertices[i] *= offset; }
    
    uint16_t getColor() const
    { return color; }
    
    void setColor(const byte r, const byte g, const byte b)
    { color = RGB(r, g, b); }
  
  
};

Shape::Shape(co

#endif //SHAPE_H
