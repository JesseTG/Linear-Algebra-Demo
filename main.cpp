#include "include/Declarations.h"
#include "include/StateManager.h"

#include <ctime>

const int SCREEN_WIDTH  = 640;  //In pixels
const int SCREEN_HEIGHT = 480;  //In pixels
const int SCREEN_BPP    = 32;   //Bits per pixel

/*
 * Created by Jesse Talavera-Greenberg
 * AP Calculus AB
 * John Czartosieski
 * May 2012
 *
 * These are comments.  Comments are NOT read by the compiler.
 */

//Returns whether the program started up OK or not.
bool init();

Image        bgimage;  //The background image.
Sprite       bg;       //The sprite that represents this background image.
Event        event;    //The latest external input
Image        sprites;  //The entire spritesheet.  All graphics taken from here.
StateManager StateController;

const RectInt     SCREEN(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT        );
const VectorFloat CENTER(SCREEN.GetWidth()/2, SCREEN.GetHeight()/2);

RenderWindow Window(sf::VideoMode(SCREEN.GetWidth(), SCREEN.GetHeight(), SCREEN_BPP),
                    "Linear Algebra Demo", sf::Style::Titlebar | sf::Style::Close  );


int main()
{
    if (!init()) return EXIT_FAILURE;

    while (true) StateController.updateState();

    return EXIT_SUCCESS;
}

bool init()
{
    //Prepare the background  //////////////////////////////////////////////////
    if (!bgimage.LoadFromFile("./gfx/bg.png")) return false;
    bgimage.SetSmooth(false);
    bg.SetImage(bgimage);
    ////////////////////////////////////////////////////////////////////////////

    //Prepare the spritesheet  /////////////////////////////////////////////////
    if (!sprites.LoadFromFile("./gfx/sprites.png")) return false;
    sprites.SetSmooth(false);
    ////////////////////////////////////////////////////////////////////////////

    //Initialize the random number generator
    Random::SetSeed(time(NULL));

    //Initializes the state manager
    StateController.init();

    return true;
}
