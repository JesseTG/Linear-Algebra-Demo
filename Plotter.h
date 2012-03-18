/*
 * This code comes from the Wireframe example for the Gameduino.
 * http://tinyurl.com/6vrfzr6
 */

#ifndef PLOTTER_H
#define PLOTTER_H

#include "wireframe.h"
#include "eraser.h"

// replicate a 2-bit color across the whole byte.
byte replicate(const byte color)
{
  return (color << 6) | (color << 4) | (color << 2) | color;
}

#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)

class PlotterClass
{
public:
  void begin();
  void line(byte x0, byte y0, byte x1, byte y1);
  void show(word color);
  inline void show();
private:
  byte flip;
  byte plotting;
  void erase();
  void waitready();
};

PlotterClass Plotter;

void PlotterClass::waitready()
{
  while (GD.rd(COMM+7));
}

void PlotterClass::erase()
{
  plotting = 0;
  GD.wr(J1_RESET, 1);
  GD.wr(COMM+7, 1);
  GD.wr(COMM+8, replicate((flip ? 1 : 2) ^ 3));
  GD.microcode(eraser_code, sizeof(eraser_code));
}

void PlotterClass::begin()
{
  // Draw 256 sprites left to right, top to bottom, all in 4-color
  // palette mode.  By doing them in column-wise order, the address
  // calculation in setpixel is made simpler.
  // First 64 use bits 0-1, next 64 use bits 2-4, etc.
  // This gives a 256 x 256 4-color bitmap.
  for (byte i = 0; i < 256; ++i) {
    GD.sprite(i,
              72 + 16 * ((i >> 4) & 15),
              22 + 16 * (i & 15),
              i & 63, /* image 0-63 */
              0x8 | ((3 - (i >> 6)) << 1), /* palettes bits in columns 3,2,1,0 */
              0);
  }

  flip = 0;
  plotting = 0;
  erase();
  show();
}

inline void PlotterClass::show()
{
  show(WHITE);
}

void PlotterClass::show(word color)
{
  waitready();
  if (flip == 1) {
    GD.wr16(PALETTE4A, BLACK);
    GD.wr16(PALETTE4A + 2, color);
    GD.wr16(PALETTE4A + 4, BLACK);
    GD.wr16(PALETTE4A + 6, color);
  } 
  else {
    GD.wr16(PALETTE4A, BLACK);
    GD.wr16(PALETTE4A + 2, BLACK);
    GD.wr16(PALETTE4A + 4, color);
    GD.wr16(PALETTE4A + 6, color);
  }
  flip ^= 1;
  erase();
}

void PlotterClass::line(byte x0, byte y0, byte x1, byte y1)
{
#define SWAP(a, b) ((a)^=(b), (b)^=(a), (a)^=(b))

  byte steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    SWAP(x0, y0);
    SWAP(x1, y1);
  }
  if (x0 > x1) {
    SWAP(x0, x1);
    SWAP(y0, y1);
  }
  int deltax = x1 - x0;
  int deltay = abs(y1 - y0);
  int error = deltax / 2;
  char ystep = (y0 < y1) ? 1 : -1;  

  byte x;
  byte y = y0;

  waitready();
  if (!plotting) {
    GD.microcode(wireframe_code, sizeof(wireframe_code));
    plotting = 1;
    GD.wr(COMM+8, (flip + 1) << 6);
  }
  GD.__wstart(COMM+0);
  SPI.transfer(x0);
  SPI.transfer(y0);
  SPI.transfer(x1);
  SPI.transfer(y1);
  SPI.transfer(steep);
  SPI.transfer(deltax);
  SPI.transfer(deltay);
  SPI.transfer(ystep);
  GD.__end();
}

#endif  //PLOTTER_H

