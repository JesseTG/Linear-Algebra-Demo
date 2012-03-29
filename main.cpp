#include "include/Declarations.h"
#include "include/StateManager.h"

StateManager StateController;

int main()
{
    Window.Display();
    Window.Clear();

    while (true) StateController.updateState();

    return 0;
}
