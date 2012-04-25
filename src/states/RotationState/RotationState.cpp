#include "../../../include/states/RotationState/RotationState.h"

const int HELI_SCALE = 3;  //In times  (e.g. 3 times bigger)
const int HELI_ROTATION = 5;  //This many degrees per frame

RotationState::RotationState()
{
    frames[currentframe = 0] = RectInt(58, 36, 85, 63);
    frames[1] = RectInt(86, 37, 113, 64);
    frames[2] = RectInt(113, 37, 140, 64);
    frames[3] = RectInt(139, 37, 166, 64);

    initSprite(helicopter, sprites, frames[0], HELI_SCALE);
    helicopter.FlipY(true);

    acceleration = VectorFloat(sin(helicopter.GetRotation()*(M_PI/180)),
                         cos(helicopter.GetRotation()*(M_PI/180)));
    velocity = VectorFloat(0, 0);

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

    acceleration = VectorFloat(sin(helicopter.GetRotation()*(M_PI/180)),
                         cos(helicopter.GetRotation()*(M_PI/180)));

    VectorFloat drag(velocity.x * -.1, velocity.y*-.1);

    if (INPUT.IsKeyDown(sf::Key::Up)) {
        helicopter.Move(velocity += acceleration);
    }
    else if (INPUT.IsKeyDown(sf::Key::Down)) {
        helicopter.Move(velocity -= acceleration);
    }

    helicopter.Move(velocity += drag);


    if (helicopter.GetPosition().x < 0) helicopter.SetX(0);
    if (helicopter.GetPosition().x > Window.GetWidth()) helicopter.SetX(Window.GetWidth());
    if (helicopter.GetPosition().y < 0) helicopter.SetY(0);
    if (helicopter.GetPosition().y > Window.GetHeight()) helicopter.SetY(Window.GetHeight());
}

void RotationState::render() const
{
    Window.Draw(bg);
    Window.Draw(helicopter);
    Window.Display();
}
