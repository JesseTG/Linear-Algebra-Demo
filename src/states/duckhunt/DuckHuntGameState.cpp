#include "../../../include/states/duckhunt/DuckHuntGameState.h"

const int BG_SCALE = 2;

enum { GROUND, GRASS, SKY };

DuckHuntGameState::DuckHuntGameState()
{
    bglayersimage.LoadFromFile("./gfx/duckhuntbg.png");
    bglayersimage.SetSmooth(false);

    for (Sprite& i : bglayers) {
        i.SetImage(bglayersimage);
        i.SetScale(BG_SCALE, BG_SCALE);
    }

    bglayers[GROUND].SetSubRect(RectInt(0, 0, 320, 240));
    bglayers[GRASS].SetSubRect(RectInt(320, 0, 640, 240));
    bglayers[SKY].SetSubRect(RectInt(0, 240, 320, 480));

    ducks[0].reset(new Duck);

}

DuckHuntGameState::~DuckHuntGameState()
{
    //dtor
}

void DuckHuntGameState::input()
{
    checkForNextState(StateName::DUCKHUNT_TITLE, StateName::NADA);
}

void DuckHuntGameState::logic()
{
    ducks[0]->fly();
}

void DuckHuntGameState::render() const
{
    Window.Draw(bglayers[SKY]);

    Window.Draw(ducks[0]->getSprite());
    Window.Draw(bglayers[GROUND]);
    Window.Draw(bglayers[GRASS]);
    Window.Display();
}
