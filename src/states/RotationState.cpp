#include "../../include/states/RotationState.h"

#include <iomanip>

const int HELI_SCALE = 3;  //In times  (e.g. 3 times bigger)
const int HELI_ROTATION = 5;  //This many degrees per frame

RotationState::RotationState()
{
    //Initializes all frames of the helicopter (and the frame counter)  ////////
    frames[currentframe = 0] = RectInt(58, 36, 85, 63);
    frames[1] = RectInt(86, 37, 113, 64);
    frames[2] = RectInt(113, 37, 140, 64);
    frames[3] = RectInt(139, 37, 166, 64);
    ////////////////////////////////////////////////////////////////////////////

    initSprite(helicopter, sprites, frames[0], HELI_SCALE);

    acceleration = VectorFloat(sin(helicopter.GetRotation()*(M_PI/180)),
                         cos(helicopter.GetRotation()*(M_PI/180)));

    bump.file.LoadFromFile("./sfx/copterbump.wav");
    bump.sound.SetBuffer(bump.file);

}

RotationState::~RotationState()
{
    //dtor
}

void RotationState::input()
{
    checkForNextState(StateName::DOT_PRODUCTS, StateName::DUCKHUNT_TITLE);

    //Rotates the helicopter if left or right are pressed  /////////////////////
    if (INPUT.IsKeyDown(sf::Key::Left)) helicopter.Rotate(HELI_ROTATION);
    else if (INPUT.IsKeyDown(sf::Key::Right)) helicopter.Rotate(-HELI_ROTATION);
    ////////////////////////////////////////////////////////////////////////////

    //Accelerates or decelerates the helicopter if up or down are pressed  /////
    if (INPUT.IsKeyDown(sf::Key::Up))
        helicopter.Move(velocity -= acceleration);
    else if (INPUT.IsKeyDown(sf::Key::Down))
        helicopter.Move(velocity += acceleration);
    ////////////////////////////////////////////////////////////////////////////
}

void RotationState::logic()
{
    helicopter.SetSubRect(frames[(++currentframe) % 4]);

    acceleration = VectorFloat(sin(helicopter.GetRotation()*(M_PI/180)),
                               cos(helicopter.GetRotation()*(M_PI/180)));

    //Adds drag (negative) to velocity, thus slowing the chopper down
    helicopter.Move(velocity += VectorFloat(velocity.x * -.1, velocity.y*-.1));

    //Ensures that the helicopter doesn't leave the screen  ////////////////////
    if (helicopter.GetPosition().x < 0) {
        velocity.x *= -1;
        helicopter.SetX(0);
        bump.Play();
    }
    if (helicopter.GetPosition().x > Window.GetWidth()) {
        velocity.x *= -1;
        helicopter.SetX(Window.GetWidth());
        bump.Play();
    }
    if (helicopter.GetPosition().y < 0) {
        velocity.y *= -1;
        helicopter.SetY(0);
        bump.Play();
    }
    if (helicopter.GetPosition().y > Window.GetHeight()) {
        velocity.y *= -1;
        helicopter.SetY(Window.GetHeight());
        bump.Play();
    }
    ////////////////////////////////////////////////////////////////////////////

    stats_to_string.str("");
    stats_to_string << "Rotation\n\n"
                    << "Angle: " << std::setprecision(0) << helicopter.GetRotation() << "\n"
                    << "Velocity: " << std::fixed << std::setprecision(3)
                    << hypot(velocity.x, velocity.y) << "\n\n"
                    << "Arrow Keys: Accelerate, Decelerate, and Steer" << "\n\n"
                    << "GFX: Micro Machines (Codemasters, 1993)";
    stats.SetText(stats_to_string.str());
}

void RotationState::render()
{
    Window.Draw(bg);
    Window.Draw(helicopter);
    Window.Draw(stats);
    Window.Display();
}
