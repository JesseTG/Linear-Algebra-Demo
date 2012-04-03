#include "include/Declarations.h"
#include "include/StateManager.h"

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

StateManager StateController;

int main()
{
    logger.log("Program start.");
    if (init()) {
        logger.log("Global resources initialized successfully.");
    }
    else {
        logger.log("Resources not properly initialized!  Exiting!");
        return EXIT_FAILURE;
    }


    Window.Clear();
    Window.Display();

    while (true) StateController.updateState();

    logger.log("Program ended normally.");
    return EXIT_SUCCESS;
}

bool init()
{
    if (bgimage.LoadFromFile("./gfx/bg.png")) logger.log("Loaded background.");
    else return false;
    bgimage.SetSmooth(false);
    bg.SetImage(bgimage);

    if (sprites.LoadFromFile("./gfx/sprites.png"))
        logger.log("Loaded spritesheet.");
    else return false;
    sprites.SetSmooth(false);

    return true;
}
