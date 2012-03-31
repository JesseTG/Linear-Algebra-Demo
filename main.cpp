#include "include/Declarations.h"
#include "include/StateManager.h"

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
        exit(1);
    }


    Window.Clear();
    Window.Display();

    while (true) StateController.updateState();

    logger.log("Program ended normally.");
    return 0;
}

bool init()
{
    if (bgimage.LoadFromFile("./gfx/bg.png")) logger.log("Loaded background.");
    else return false;
    bg.SetImage(bgimage);

    if (font.LoadFromFile("./gfx/font.ttf")) logger.log("Loaded font.");
    else return false;

    return true;
}
