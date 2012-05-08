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

    {  //Prepare member variables  /////////////////////////////////////////////
    ammo             = 3;
    can_shoot        = false;
    dog_behind_grass = false;
    is_screen_flash  = false;
    state            = InGameState::INTRO;
    }

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
    button_down      = INPUT.IsMouseButtonDown(sf::Mouse::Left);
    if (button_down && !button_last_down && can_shoot) shoot();
}

void DuckHuntGameState::logic()
{
    prevstate = state;

    switch (state) {
        case InGameState::INTRO     : intro();      break;
        case InGameState::GAME      : game();       break;
        case InGameState::ROUND_END : round_end();  break;
        case InGameState::ROUND_WIN : round_win();  break;
        case InGameState::ROUND_FAIL:               break;
        case InGameState::GAME_OVER : game_over();  break;
        default: throw std::invalid_argument("Game state not recognized!");
    }

    if (flashtimer.GetElapsedTime() > FLASH_LENGTH && is_screen_flash) {
        is_screen_flash = false;
        can_shoot = true;
    }



    for (auto& i : ducks) i.act();
    dog.act();
}

void DuckHuntGameState::render()
{
    for (auto& i : ducks) i.updateAnimation();
    dog.updateAnimation();

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
    if (sounds[DuckHuntSound::INTRO].sound.GetStatus() == sf::Sound::Stopped) {
        if (dog.getState() == DogState::WALKING) dog.setState(DogState::JUMPING_UP);
    }

    //If the dog is behind the bush...
    if (dog.getState() == DogState::JUMPING_DOWN && !dog_behind_grass) {
        dog_behind_grass = true;
        std::swap(renderlist[3], renderlist[5]);
    }

    //If the dog has landed on the ground...
    if (dog.getState() == DogState::IDLE) {
        can_shoot = true;
        for (auto& i : ducks) i.setState(DuckState::FLYING_IN);
        state = InGameState::GAME;
    }
}

void DuckHuntGameState::game()
{
    if (ammo <= 0) {
        for (auto& i : ducks)
            if (i.getState() == DuckState::FLYING_AROUND)
                i.setState(DuckState::FLYING_OUT);
        state = InGameState::ROUND_END;
    }
}

void DuckHuntGameState::game_over()
{

}

void DuckHuntGameState::round_end()
{
    //switch (ducks_dead)
}

void DuckHuntGameState::shoot()
{
    if (can_shoot && !is_screen_flash && ammo > 0) {
        sounds[DuckHuntSound::SHOT].Play();
        flashtimer.Reset();
        is_screen_flash = true;
        can_shoot = false;
        --ammo;

        for (auto& i : ducks) {
            if (i.getShotBox().Contains(MOUSE) && i.getState() == DuckState::FLYING_AROUND) {
                ++ducks_dead;
                std::cout << int(ducks_dead) << std::endl;
                i.setState(DuckState::SHOT);
            }
        }

        if (ducks_dead == 2) {
            state = InGameState::ROUND_END;
        }
    }

}
