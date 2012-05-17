#include "../../include/states/RotationState.h"

const int   HELI_SCALE    =   3;  //In times  (e.g. 3 times bigger)
const int   HELI_ROTATION =   5;  //This many degrees per frame
const float HELI_DRAG     = -.1;  //By how much percentage the helicopter's speed falls per frame

RotationState::RotationState()
{
    //Initializes all frames of the helicopter (and the frame counter)
    frames[0] = RectInt( 58,  36,  85,  63);
    frames[1] = RectInt( 86,  37, 113,  64);
    frames[2] = RectInt(113,  37, 140,  64);
    frames[3] = RectInt(139,  37, 166,  64);

    initSprite(helicopter, sprites, frames[0], HELI_SCALE);

    //The vector that gives the direction we accelerate in
    acceleration = VectorFloat(sin(helicopter.GetRotation()*(M_PI/180)), cos(helicopter.GetRotation()*(M_PI/180)));

    //Loads the bump sound effect
    bump.Load("./sfx/copterbump.wav");
}

void RotationState::input()
{
    checkForNextState(StateName::DOT_PRODUCTS, StateName::DUCKHUNT_TITLE);

    //Rotates the helicopter if left or right are pressed
    if (INPUT.IsKeyDown(sf::Key::Left)) helicopter.Rotate(HELI_ROTATION);
    else if (INPUT.IsKeyDown(sf::Key::Right)) helicopter.Rotate(-HELI_ROTATION);

    //Accelerates or decelerates the helicopter if up or down are pressed
    if (INPUT.IsKeyDown(sf::Key::Up))
        helicopter.Move(velocity -= acceleration);  //Go forward (positive acceleration); y-axis is inverted in computers!
    else if (INPUT.IsKeyDown(sf::Key::Down))
        helicopter.Move(velocity += acceleration);  //Go backward (negative acceleration)
}

void RotationState::logic()
{
    //Animates based on how much time has passed
    helicopter.SetSubRect(frames[int(animationtimer.GetElapsedTime()*1500) % 4]);  //% means modulo; returns remainder

    //Sets acceleration based on direction
    acceleration = VectorFloat(sin(helicopter.GetRotation()*(M_PI/180)), cos(helicopter.GetRotation()*(M_PI/180)));

    //Adds drag (negative) to velocity, thus slowing the chopper down
    helicopter.Move(velocity += (velocity * HELI_DRAG));

    //If we're outside the screen on the x axis...
    if (helicopter.GetPosition().x < 0 || helicopter.GetPosition().x > SCREEN.GetWidth()) {
        velocity.x *= -1;  //Negate velocity to bounce back
        helicopter.SetX(helicopter.GetPosition().x < 0 ? 0 : SCREEN.GetWidth());  //Move to left or right edges
        bump.Play();
    }
    if (helicopter.GetPosition().y < 0 || helicopter.GetPosition().y > SCREEN.GetHeight()) {
        velocity.y *= -1;
        helicopter.SetY(helicopter.GetPosition().y < 0 ? 0 : SCREEN.GetHeight());
        bump.Play();
    }

    //Sets up text for display
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
    Window.Draw(bg        );
    Window.Draw(helicopter);
    Window.Draw(stats     );
    Window.Display();
}
