#include "../../../include/states/duckhunt/DuckHuntTitle.h"

const int LOGO_SCALE = 3;

DuckHuntTitle::DuckHuntTitle()
{
    initSprite(logo, sprites, RectInt(0, 98, 192, 194), LOGO_SCALE,
               VectorFloat(center.x, Window.GetHeight()/3));

    font.LoadFromFile("./gfx/emulogic.ttf");
    text.SetFont(font);
    text.SetText("Press P to Start");
    text.SetPosition(Window.GetWidth()/6, 3*Window.GetHeight()/4);

    titlejinglefile.LoadFromFile("./sfx/duckhunt/title.wav");
    titlejingle.SetBuffer(titlejinglefile);
    titlejingle.Play();

    Window.Clear();
    Window.Draw(logo);
    Window.Draw(text);
    Window.Display();
}

DuckHuntTitle::~DuckHuntTitle()
{
    titlejingle.Stop();
}

void DuckHuntTitle::input()
{
    checkForNextState(StateName::ROTATION, StateName::DUCKHUNT_GAME);
}
