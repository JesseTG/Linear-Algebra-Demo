#include "../../../include/states/duckhunt/DuckHuntGameState.h"

const int BG_SCALE = 2;
const float FLASH_LENGTH = .1;

enum { GROUND, GRASS, SKY };

DuckHuntGameState::DuckHuntGameState()
{

    {  //Prepare background  ///////////////////////////////////////////////////
    bglayersimage.LoadFromFile("./gfx/duckhuntbg.png");
    bglayersimage.SetSmooth(false);

    //Create the background and scale it properly
    for (Sprite& i : bglayers) {
        i.SetImage(bglayersimage     );
        i.SetScale(BG_SCALE, BG_SCALE);
    }

    //Assign the three layers to different segments
    bglayers[GROUND].SetSubRect(RectInt(  0,   0, 320, 240));
    bglayers[GRASS ].SetSubRect(RectInt(320,   0, 640, 240));
    bglayers[SKY   ].SetSubRect(RectInt(  0, 240, 320, 480));
    }


    {  //Prepare sounds  ///////////////////////////////////////////////////////
    sounds[DuckHuntSound::SHOT ].file.LoadFromFile("./sfx/duckhunt/shot.wav"        );
    sounds[DuckHuntSound::SHOT ].sound.SetBuffer(sounds[DuckHuntSound::SHOT].file   );
    sounds[DuckHuntSound::INTRO].file.LoadFromFile("./sfx/duckhunt/intro.wav"       );
    sounds[DuckHuntSound::INTRO].sound.SetBuffer(sounds[DuckHuntSound::INTRO].file  );
    }


    {  //Prepare objects  //////////////////////////////////////////////////////
    }

    {  //Prepare render list  //////////////////////////////////////////////////
    renderlist.push_back(&bglayers[SKY]       );
    renderlist.push_back(&ducks[0].getSprite());
    renderlist.push_back(&ducks[1].getSprite());
    renderlist.push_back(&bglayers[GROUND]    );
    renderlist.push_back(&bglayers[GRASS]     );
    renderlist.push_back(&dog.getSprite()     );
    }

    {  //Prepare member variables  /////////////////////////////////////////////
    ammo             = 3;
    can_shoot        = false;
    dog_behind_grass = false;
    ducks_dead       = 0;
    is_screen_flash  = false;
    round            = 1;
    setState(InGameState::INTRO);
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
    if (state == InGameState::GAME && button_down && !button_last_down) shoot();
}

void DuckHuntGameState::logic()
{
    prevstate = state;
    std::cout << "State: " << int(state) << std::endl;
    std::cout << "Ducks Dead: " << int(ducks_dead) << std::endl;

    switch (state) {
        case InGameState::INTRO      : intro();       break;
        case InGameState::GAME       : game();        break;
        case InGameState::ROUND_START: round_start(); break;
        case InGameState::ROUND_END  : round_end();   break;
        case InGameState::ROUND_WIN  : round_win();   break;
        case InGameState::ROUND_FAIL : round_fail();  break;
        case InGameState::GAME_OVER  : game_over();   break;
        default: throw std::invalid_argument("Game state not recognized!");
    }

    //If the screen has been white for long enough...
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
    //If the intro theme is not playing anymore...
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
        setState(InGameState::ROUND_START);
    }
}

void DuckHuntGameState::game()
{
    //Let the ducks loose
    if (prevstate == InGameState::ROUND_START) {
        for (auto& i : ducks) i.setState(DuckState::FLYING_IN);
    }

    //If we run out of ammo, time, or ducks to shoot...
    if (ammo <= 0 || timepassed.GetElapsedTime() >= 5 || ducks_dead == 2) {
        for (auto& i : ducks)
            if (i.getState() == DuckState::FLYING_AROUND)  //If they haven't died...
                i.setState(DuckState::FLYING_OUT);  //The ducks fly away
        setState(InGameState::ROUND_END);
    }

}

void DuckHuntGameState::round_start()
{
    can_shoot = true;
    is_screen_flash = false;
    ducks_dead = 0;
    ++round;
    timepassed.Reset();

    setState(InGameState::GAME);
}

void DuckHuntGameState::game_over()
{

}

void DuckHuntGameState::round_end()
{
    if (!IN_RANGE(ducks[0].getSprite().GetPosition().y, 0, Window.GetHeight()*.7) &&
        !IN_RANGE(ducks[1].getSprite().GetPosition().y, 0, Window.GetHeight()*.7)) {
        switch (ducks_dead) {
            case 0: dog.setState(DogState::LAUGHING     ); setState(InGameState::ROUND_FAIL);  break;
            case 1: dog.setState(DogState::HOLDING_1DUCK); setState(InGameState::ROUND_WIN );  break;
            case 2: dog.setState(DogState::HOLDING_2DUCK); setState(InGameState::ROUND_WIN );  break;
            default: throw std::out_of_range("Wrong amount of ducks died!  (Should not be " + boost::lexical_cast<std::string, int>(ducks_dead) + ")");
        }
    }
}

void DuckHuntGameState::round_win()
{
    if (actiontimer.GetElapsedTime() >= 5 && dog.getState() != DogState::HOLDING_1DUCK &&
        dog.getState() != DogState::HOLDING_2DUCK)
            setState(InGameState::ROUND_START);
}

void DuckHuntGameState::round_fail()
{
    if (actiontimer.GetElapsedTime() >= 5 && dog.getState() != DogState::LAUGHING)
        setState(InGameState::ROUND_START);
}

void DuckHuntGameState::shoot()
{
    if (can_shoot && !is_screen_flash && ammo > 0) {
        sounds[DuckHuntSound::SHOT].Play();
        flashtimer.Reset();
        is_screen_flash = true;
        can_shoot       = false;
        --ammo;

        for (auto& i : ducks) {
            if (i.getShotBox().Contains(MOUSE) && i.getState() == DuckState::FLYING_AROUND) {
                i.setState(DuckState::SHOT);
                ++ducks_dead;
            }
        }
    }

}
