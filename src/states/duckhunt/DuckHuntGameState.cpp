#include "../../../include/states/duckhunt/DuckHuntGameState.h"

const int BG_SCALE = 2;
const float FLASH_LENGTH = .1;

enum { GROUND, GRASS, SKY };

DuckHuntGameState::DuckHuntGameState()
{

    {  //Prepare background  ///////////////////////////////////////////////////
    bglayersimage.LoadFromFile("./gfx/duckhuntbg.png");
    bglayersimage.SetSmooth(false);

    for (Sprite& i : bglayers) {
        i.SetImage(bglayersimage);
        i.SetScale(BG_SCALE, BG_SCALE);
    }

    bglayers[GROUND].SetSubRect(RectInt(0, 0, 320, 240));
    bglayers[GRASS].SetSubRect(RectInt(320, 0, 640, 240));
    bglayers[SKY].SetSubRect(RectInt(0, 240, 320, 480));
    }


    {  //Prepare sounds  ///////////////////////////////////////////////////////
    sounds[DuckHuntSound::SHOT].file.LoadFromFile("./sfx/duckhunt/shot.wav");
    sounds[DuckHuntSound::SHOT].sound.SetBuffer(sounds[DuckHuntSound::SHOT].file);
    sounds[DuckHuntSound::INTRO].file.LoadFromFile("./sfx/duckhunt/intro.wav");
    sounds[DuckHuntSound::INTRO].sound.SetBuffer(sounds[DuckHuntSound::INTRO].file);
    }


    {  //Prepare objects  //////////////////////////////////////////////////////
    }

    {  //Prepare render list  //////////////////////////////////////////////////
    renderlist.push_back(&bglayers[SKY]);
    renderlist.push_back(&ducks[0].getSprite());
    renderlist.push_back(&ducks[1].getSprite());
    renderlist.push_back(&bglayers[GROUND]);
    renderlist.push_back(&bglayers[GRASS]);
    renderlist.push_back(&dog.getSprite());
    }

    //Prepare member variables  ////////////////////////////////////////////////
    can_shoot = false;
    is_screen_flash = false;
    state = InGameState::INTRO;
    ////////////////////////////////////////////////////////////////////////////

    sounds[DuckHuntSound::INTRO].Play();
}

DuckHuntGameState::~DuckHuntGameState()
{
    //dtor
}

void DuckHuntGameState::input()
{
    checkForNextState(StateName::DUCKHUNT_TITLE, StateName::NADA);
    button_last_down = button_down;
    button_down = INPUT.IsMouseButtonDown(sf::Mouse::Left);
    if (button_down == true && button_last_down == false && can_shoot) {
        shoot();
    }
}

void DuckHuntGameState::logic()
{
    switch (state) {
        case InGameState::INTRO     :  intro();      break;
        case InGameState::GAME      :  game();       break;
        case InGameState::ROUND_OVER:  round_over(); break;
        case InGameState::GAME_OVER :  game_over();  break;
        default: throw std::invalid_argument("Game state not recognized!");

    }


    if (flashtimer.GetElapsedTime() > FLASH_LENGTH && is_screen_flash) {
        is_screen_flash = false;
        can_shoot = true;
    }

    for (auto& i : ducks) i.act();
}

void DuckHuntGameState::render()
{
    for (auto& i : ducks) i.updateAnimation();

    if (!is_screen_flash) {
        for (const auto& i : renderlist) Window.Draw(*i);
    }
    else {
        Window.Clear(Color::White);
    }

    Window.Display();
}

void DuckHuntGameState::intro()
{
    if (dog.getState() != DogState::IDLE && sounds[DuckHuntSound::INTRO].sound.GetStatus() == sf::Sound::Playing) {
        can_shoot = false;
        dog.getSprite().Move(sounds[DuckHuntSound::INTRO].file.GetDuration()/7, 0);
        dog.animate();
    } else {
        state = InGameState::GAME;
        dog.setState(DogState::IDLE);
        for (auto& i : ducks) i.setState(DuckState::FLYING_IN);
        can_shoot = true;
    }
}

void DuckHuntGameState::game_over()
{

}

void DuckHuntGameState::round_over()
{

}

void DuckHuntGameState::game()
{
    for (auto& i : ducks) i.act();
}

void DuckHuntGameState::shoot()
{
    if (can_shoot && !is_screen_flash) {
        sounds[DuckHuntSound::SHOT].Play();
        flashtimer.Reset();
        is_screen_flash = true;
        can_shoot = false;

        for (auto& i : ducks) {
            if (i.getShotBox().Contains(INPUT.GetMouseX(), INPUT.GetMouseY()) && i.getState() == DuckState::FLYING_AROUND) {
                i.setState(DuckState::SHOT);
            }
        }
    }

}
