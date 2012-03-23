#include "Declarations.h"

#include "NumMatrix.h"
#include "Vector.h"
#include "Shape.h"

#include "StateManager.h"
#include "State.h"
#include "TitleState.h"

#include "bgtile.h"
#include "Plotter.h"

#include <SPI/SPI.h>
#include <GD.h>

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
