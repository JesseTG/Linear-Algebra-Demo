#include "include/Declarations.h"

#include "include/NumMatrix.h"
#include "include/Vector.h"
#include "include/Shape.h"

#include "include/StateManager.h"
#include "include/State.h"
#include "include/TitleState.h"

#include "include/etc/bgtile.h"
#include "include/etc/Plotter.h"

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
