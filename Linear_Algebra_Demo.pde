#include <SPI.h>
#include <GD.h>
#include <font8x8.h>

#include "Declarations.h"

StateManager StateController;

void setup()
{
  GD.begin();
  Plotter.begin();

  for (byte y = 0; y < 2; y++)
    GD.copy(RAM_PIC + y * 64, bgtile_pic + y * 2, 2);
  GD.copy(RAM_CHR, bgtile_chr, sizeof(bgtile_chr));
  GD.copy(RAM_PAL, bgtile_pal, sizeof(bgtile_pal));
  
  
  
}

void loop()
{
  
}
