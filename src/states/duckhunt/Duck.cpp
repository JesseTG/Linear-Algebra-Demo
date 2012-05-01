#include "../../../include/states/duckhunt/Duck.h"

Duck::Duck()
{
    sprite.SetImage(sprites);
    sprite.SetSubRect(RectInt(0, 197, 29, 228));
}

Duck::~Duck()
{
    //dtor
}

void Duck::fly()
{
    sprite.SetPosition(INPUT.GetMouseX(), INPUT.GetMouseY());
}

void Duck::flyAway()
{

}
