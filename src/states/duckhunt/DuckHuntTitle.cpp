#include "../../../include/states/duckhunt/DuckHuntTitle.h"

const int LOGO_SCALE = 3;

DuckHuntTitle::DuckHuntTitle()
{
    initSprite(logo, sprites, RectInt(0, 98, 192, 194), LOGO_SCALE,
               VectorFloat(CENTER.x, SCREEN.GetHeight()/3));

    font.LoadFromFile("./gfx/emulogic.ttf");
    text.SetFont(font);
    text.SetSize(16);
    text.SetText("Sounds and Graphics Copyright Nintendo\n"
                 "Mouse: Shoot Ducks\n"
                 "Goal: Score high, do not miss too many\n\n"
                 "Press P to Start");
    text.SetPosition(SCREEN.GetWidth()*.03, SCREEN.GetHeight()*.65);

    titlejingle.file.LoadFromFile("./sfx/duckhunt/title.wav");
    titlejingle.sound.SetBuffer(titlejingle.file);
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
