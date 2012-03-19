#ifndef SHAPE_H
#define SHAPE_H

#include <GD.h>
#include "Declarations.h"
#include "Plotter.h"


class Shape
{
  private:
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
      for (byte i = 0; i < numofvertices; ++i)
        Plotter.line(vertices[i%numofvertices].getTransformedVector().x,
                     vertices[i%numofvertices].getTransformedVector().y,
                     vertices[(i+1)%numofvertices].getTransformedVector().x,
                     vertices[(i+1)%numofvertices].getTransformedVector().y);
    }
    
    void setVertice(const byte vertice, const Vector& newpos)
    { vertices[vertice](0, 2) = newpos.x; vertices[vertice](1, 2) = newpos.y; }
    
    void setAngle(const int16_t newangle);
    
    void rotateBy(const int16_t theangle);
    
    void shearBy(const Vector& offset);
    
    void shearTo(const Vector& offset);
    
    void scaleBy(const Vector& offset);
    
    void setPosition(const Vector& offset);  //Uses first point.
    
    void moveBy(const Vector& offset);
    
    void moveTo(const Vector& offset);
    
    //Transforms all points in this Shape by this matrix.
    void transform(const NumMatrix& offset)
    { for (byte i = 0; i < numofvertices; ++i) vertices[i] *= offset; }
    
    uint16_t getColor() const
    { return color; }
    
    void setColor(const byte r, const byte g, const byte b)
    { color = RGB(r, g, b); }
  
  
};

#endif //SHAPE_H
