#include "include/Declarations.h"
#include "include/StateManager.h"

#include <ctime>

/*
 * Created by Jesse Talavera-Greenberg
 *
 * These are comments.  Comments are NOT read by the compiler.
 *
 * This code was written with an editor that suppoprted syntax highlighting.
 * Without it, it's nigh impossible to read.  Therefore, you might want to paste
 * this code into ideone.com with C++ mode and syntax highlighting enabled.
 */

//Returns whether the program started up OK or not.
bool init();

RenderWindow Window(sf::VideoMode(640, 480, 32), "Linear Algebra Demo",
                    sf::Style::Titlebar | sf::Style::Close);

Image bgimage;  //The background image.
Sprite bg;  //The sprite that represents this background image.
const VectorFloat center(Window.GetWidth()/2, Window.GetHeight()/2);
Event event;  //The object the latest event (external input) is stored in
Image sprites;  //The entire spritesheet.  All graphics taken from here.
StateManager StateController;

int main()
{
    if (!init()) return EXIT_FAILURE;

    Random::SetSeed(time(NULL));

    Window.Clear();
    Window.Display();

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

    return true;
}
