#include "include/Declarations.h"

#include "include/NumMatrix.h"
#include "include/Vector.h"
#include "include/Shape.h"

#include "include/StateManager.h"
#include "include/State.h"
#include "include/states/TitleState.h"

#include "include/etc/bgtile.h"
#include "include/etc/Plotter.h"

#include <SPI/SPI.h>
#include <GD.h>

//So I don't need to change these values in multiple places
const byte RECEIVER_PIN = 10;

StateManager statecontroller;  //Manages states in this program.
IRrecv receiver(RECEIVER_PIN);  //Represents the IR receiver.
decode_results results;  //Stores what the IRrecv reads.

//This function is called once.  Required by all Arduino programs.
void setup()
{
  GD.begin();
  Plotter.begin();
  receiver.enableIRIn();

  for (byte y = 0; y < 2; y++)
    GD.copy(RAM_PIC + y * 64, bgtile_pic + y * 2, 2);
  GD.copy(RAM_CHR, bgtile_chr, sizeof(bgtile_chr));
  GD.copy(RAM_PAL, bgtile_pal, sizeof(bgtile_pal));

}

//This function is looped indefinitely.  Also required by Arduino programs.
void loop()
{
    statecontroller.updateState();
}
