#include "../../../include/states/RotationState/RotationState.h"

const int HELI_SCALE = 3;  //In times  (e.g. 3 times bigger)
const int HELI_ROTATION = 5;  //In degrees


RotationState::RotationState()
{
    frames[currentframe = 0] = RectInt(58, 36, 85, 63);
    frames[1] = RectInt(86, 37, 113, 64);
    frames[2] = RectInt(113, 37, 140, 64);
    frames[3] = RectInt(139, 37, 166, 64);

    initSprite(helicopter, sprites, frames[0], HELI_SCALE);
    helicopter.FlipY(true);
}

RotationState::~RotationState()
{
    //dtor
}

void RotationState::input()
{
    checkForNextState(StateName::REFLECTION, StateName::NADA);
}

void RotationState::logic()
{
    helicopter.SetSubRect(frames[(++currentframe) % 4]);
    if (INPUT.IsKeyDown(sf::Key::Left)) helicopter.Rotate(HELI_ROTATION);
    else if (INPUT.IsKeyDown(sf::Key::Right)) helicopter.Rotate(-HELI_ROTATION);

    VectorFloat position(sin(helicopter.GetRotation()*(M_PI/180)),
                         cos(helicopter.GetRotation()*(M_PI/180)));
    position = position * 3;


    if (INPUT.IsKeyDown(sf::Key::Up))
        helicopter.Move(position);
    else if (INPUT.IsKeyDown(sf::Key::Down))
        helicopter.Move(-position);



}

void RotationState::render() const
{
    Window.Draw(bg);
    Window.Draw(helicopter);
    Window.Display();
}
