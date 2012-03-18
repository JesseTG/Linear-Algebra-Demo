#ifndef SHAPE_H
#define SHAPE_H

#include <GD.h>
#include "Declarations.h"
#include "Plotter.h"

template<byte numofvertices>
class Shape
{
  private:
    NumMatrix vertices[numofvertices];
    uint16_t color;
    int16_t angle;
    
  public:
    Shape()
    {
      color = RGB(255, 255, 255);
      angle = 0;
      for (byte i = 0; i < numofvertices; ++i) vertices[i] = Vector<byte>(0, 0);
    }
      
    void draw() const
    {
      for (byte i = 0; i < numofvertices; ++i)
        Plotter.line(vertices[i%numofvertices].getTransformedVector().x,
                     vertices[i%numofvertices].getTransformedVector().y,
                     vertices[(i+1)%numofvertices].getTransformedVector().x,
                     vertices[(i+1)%numofvertices].getTransformedVector().y);
    }
    
    void setVertice(const byte vertice, const Vector<byte>& coord);
    
    void setAngle(const int16_t newangle);
    
    void rotateBy(const int16_t theangle);
    
    void shearBy(const Vector<byte>& offset);
    
    void shearTo(const Vector<byte>& offset);
    
    void scaleBy(const Vector<byte>& offset);
    
    void setPosition(const Vector<byte>& offset);  //Uses first point.
    
    void moveBy(const Vector<byte>& offset);
    
    void moveTo(const Vector<byte>& offset);
    
    void transform(const NumMatrix& offset);
    
    void getTransformed(const NumMatrix& offset);
    
    
    uint16_t getColor() const
    { return color; }
    
    void setColor(const byte r, const byte g, const byte b)
    { color = RGB(r, g, b); }
  
  
};

#endif //SHAPE_H
