#include "../../../include/states/duckhunt/DuckHuntGameState.h"

const int BG_SCALE         = 2;
const float FLASH_LENGTH   = .1;  //How long each flash lasts in seconds
const float TIME_LIMIT     = 5.0;  //In seconds

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

    hudstats[HUDStat::AMMO ].SetSize(16  );
    hudstats[HUDStat::AMMO ].SetPosition( 28, 435);
    hudstats[HUDStat::ROUND].SetFont(font);
    hudstats[HUDStat::ROUND].SetSize(16  );
    hudstats[HUDStat::ROUND].SetPosition(108, 435);
    hudstats[HUDStat::SCORE].SetSize(8   );
    hudstats[HUDStat::SCORE].SetPosition(174, 435);
    hudstats[HUDStat::STATS].SetSize(8   );
    hudstats[HUDStat::STATS].SetPosition(15, 422);
    hudstats[HUDStat::STATS].SetText("AMMO      ROUND     SCORE     QUOTA");
    hudstats[HUDStat::QUOTA].SetSize(8   );
    hudstats[HUDStat::QUOTA].SetPosition(255, 435);
    hudstats[HUDStat::GAME_OVER].SetSize(48);
    hudstats[HUDStat::GAME_OVER].SetPosition(0, CENTER.y - 128);
    hudstats[HUDStat::GAME_OVER].SetText("GAME OVER");

    for (auto& i : hudstats) i.second.SetFont(font);
    }


    {  //Prepare sounds  ///////////////////////////////////////////////////////
    sounds[DuckHuntSound::SHOT ].file.LoadFromFile("./sfx/duckhunt/shot.wav"        );
    sounds[DuckHuntSound::SHOT ].sound.SetBuffer(sounds[DuckHuntSound::SHOT].file   );
    sounds[DuckHuntSound::INTRO].file.LoadFromFile("./sfx/duckhunt/intro.wav"       );
    sounds[DuckHuntSound::INTRO].sound.SetBuffer(sounds[DuckHuntSound::INTRO].file  );
    }

    {  //Prepare render list  //////////////////////////////////////////////////
    renderlist.push_back(&bglayers[SKY   ]        );
    renderlist.push_back(&ducks[0].getSprite()    );
    renderlist.push_back(&ducks[1].getSprite()    );
    renderlist.push_back(&bglayers[GROUND]        );
    renderlist.push_back(&bglayers[GRASS ]        );
    renderlist.push_back(&dog.getSprite()         );
    renderlist.push_back(&hudstats[HUDStat::AMMO ]);
    renderlist.push_back(&hudstats[HUDStat::ROUND]);
    renderlist.push_back(&hudstats[HUDStat::SCORE]);
    renderlist.push_back(&hudstats[HUDStat::QUOTA]);
    renderlist.push_back(&hudstats[HUDStat::STATS]);
    renderlist.push_back(&crosshair               );
    }

    {  //Prepare member variables  /////////////////////////////////////////////
    ammo             = 3;
    can_shoot        = false;
    dog_behind_grass = false;
    ducks_dead       = 0;
    font.LoadFromFile("./gfx/emulogic.ttf");
    is_screen_flash  = false;
    miss_left        = 3;
    round            = 0;
    score            = 0;
    total_shot       = 0;


    initSprite(crosshair, sprites, RectInt(194, 152, 212, 170), BG_SCALE, MOUSE);
    Window.ShowMouseCursor(false);  //The crosshair IS the cursor

    setState(InGameState::INTRO);

    }


    sounds[DuckHuntSound::INTRO].Play();
}

DuckHuntGameState::~DuckHuntGameState()
{
    Window.ShowMouseCursor(true);  //Best let the other screens have the cursor!
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

    //Update the status displays
    hudstats[HUDStat::AMMO ].SetText(boost::lexical_cast<std::string, int>(ammo ));
    hudstats[HUDStat::ROUND].SetText(boost::lexical_cast<std::string, int>(round));
    hudstats[HUDStat::SCORE].SetText(boost::lexical_cast<std::string, int>(score));
    hudstats[HUDStat::QUOTA].SetText(boost::lexical_cast<std::string, int>(total_shot) + "/" + boost::lexical_cast<std::string, int>(round));

    for (auto& i : ducks) i.act();
    dog.act();
    crosshair.SetPosition(MOUSE);
}

void DuckHuntGameState::render()
{
    //Animate the dog and ducks
    for (auto& i : ducks) i.updateAnimation();
    dog.updateAnimation();



    if (!is_screen_flash) {  //If the screen currently isn't flashing white...
        for (const auto& i : renderlist) Window.Draw(*i);  //Draw everything on the render list, from back to front
    }
    else {
        Window.Clear(Color::White);  //Or else flash the screen white
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
        setState(InGameState::ROUND_START);
    }
}

void DuckHuntGameState::game()
{
    //If we run out of ammo, time, or ducks to shoot...
    if (ammo <= 0 || timepassed.GetElapsedTime() >= TIME_LIMIT || ducks_dead == 2) {
        for (auto& i : ducks)
            if (i.getState() == DuckState::FLYING_AROUND || i.getState() == DuckState::FLYING_IN)  //If they haven't died...
                i.setState(DuckState::FLYING_OUT);  //The ducks fly away
        time_used = TIME_LIMIT - timepassed.GetElapsedTime();
        setState(InGameState::ROUND_END);
    }

}

void DuckHuntGameState::round_start()
{
    //Reset all necessary variables
    ammo            = 3;
    can_shoot       = true;
    ducks_dead      = 0;
    is_screen_flash = false;
    Duck::increaseDifficulty(++round);
    for (auto& i : ducks) i.setState(DuckState::FLYING_IN);

    setState(InGameState::GAME);
}

void DuckHuntGameState::game_over()
{
    if (renderlist.back() == &crosshair) renderlist.back() = &hudstats[HUDStat::GAME_OVER];
}

void DuckHuntGameState::round_end()
{
    //If we failed to meet the quota for ducks shot...
    if (total_shot < round) setState(InGameState::GAME_OVER);

    if (timepassed.GetElapsedTime() >= 1) {
        if (!SCREEN.Contains(ducks[0].getSprite().GetPosition().x, ducks[0].getSprite().GetPosition().y) &&
            !SCREEN.Contains(ducks[1].getSprite().GetPosition().x, ducks[1].getSprite().GetPosition().y)) {
                score += (ducks_dead > 0)*(time_used * 100 * (ammo+1) + round*10 + ducks_dead*300);  //Increase the score
                switch (ducks_dead) {
                    case 0: dog.setState(DogState::LAUGHING     ); setState(InGameState::ROUND_FAIL);  break;
                    case 1: dog.setState(DogState::HOLDING_1DUCK); setState(InGameState::ROUND_WIN );  break;
                    case 2: dog.setState(DogState::HOLDING_2DUCK); setState(InGameState::ROUND_WIN );  break;
                    default: throw std::out_of_range("Wrong amount of ducks died!  (Should not be " + boost::lexical_cast<std::string, int>(ducks_dead) + ")");
            }
        }
    }
}

void DuckHuntGameState::round_win()
{
    if (dog.getState() == DogState::IDLE) {
        setState(InGameState::ROUND_START);
    }
}

void DuckHuntGameState::round_fail()
{
    if (dog.getState() == DogState::IDLE)
        setState(InGameState::ROUND_START);
}

void DuckHuntGameState::shoot()
{
    //If we can currently shoot (have ammo, screen's not flashing, we have permission)...
    if (can_shoot && !is_screen_flash && ammo > 0) {
        sounds[DuckHuntSound::SHOT].Play();
        flashtimer.Reset();
        is_screen_flash = true;
        can_shoot       = false;
        --ammo;

        //Check both ducks for whether our mouse is on top of them
        for (auto& i : ducks) {
            if ((i.getState() == DuckState::FLYING_IN || i.getState() == DuckState::FLYING_AROUND) && i.getShotBox().Contains(MOUSE.x, MOUSE.y)) {
                    i.setState(DuckState::SHOT);
                    ++ducks_dead;
                    ++total_shot;
            }
        }
    }

}
