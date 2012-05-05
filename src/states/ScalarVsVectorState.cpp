#include "../../include/states/ScalarVsVectorState.h"

ScalarVsVectorState::ScalarVsVectorState()
{
    initSprite(harrier, sprites, RectInt(0, 49, 24, 96), HARRIER_SCALE);

    distance = 0;

    setSpriteBuffer(harrier, buffer);

    centerline = Shape::Line(harrier.GetPosition(), center, 5, Color::White);
    ////////////////////////////////////////////////////////////////////////////
}

void ScalarVsVectorState::input()
{
    checkForNextState(StateName::VECTORS, StateName::RASTER_VS_VECTOR);

    ismoving[UP   ] = INPUT.IsKeyDown(sf::Key::Up   );
    ismoving[DOWN ] = INPUT.IsKeyDown(sf::Key::Down );
    ismoving[LEFT ] = INPUT.IsKeyDown(sf::Key::Left );
    ismoving[RIGHT] = INPUT.IsKeyDown(sf::Key::Right);
}

void ScalarVsVectorState::logic()
{
    //Stores where we are for further calculation
    VectorFloat currentpos = harrier.GetPosition();

    inputmove(HARRIER_MOVE_SPEED, ismoving, harrier, buffer);

    //Adds the distance we just moved to the running total
    currentpos -= harrier.GetPosition();
    distance += hypot(currentpos.x, currentpos.y);

    //Changes the harrier's sprite based on which third of the screen he's in  /
    if (harrier.GetPosition().x < Window.GetWidth()/3) {
        harrier.SetSubRect(RectInt(25, 49, 48, 96));
        harrier.FlipX(true);
    }
    else if (harrier.GetPosition().x >= Window.GetWidth()/3 &&
             harrier.GetPosition().x <= 2*Window.GetWidth()/3) {
        harrier.SetSubRect(RectInt(0, 49, 24, 96));
        harrier.FlipX(false);  //The Harrier faces the center
    }
    else if (harrier.GetPosition().x > 2*Window.GetWidth()/3) {
        harrier.SetSubRect(RectInt(25, 49, 48, 96));
        harrier.FlipX(false);
    }
    ////////////////////////////////////////////////////////////////////////////


    //Prepares all statistics for output on-screen  ////////////////////////////
    VectorFloat distancetocenter = harrier.GetPosition() - center;
    stats_to_string.str("");
    stats_to_string << "Vectors Vs. Scalars\n\n"
                    << "Distance Travelled: " << distance << "\n"
                    << "Displacement From Center: " << std::setprecision(3)
                    << hypot(distancetocenter.x, distancetocenter.y) << "\n\n"
                    << "Arrow Keys: Move" << "\n\n"
                    << "GFX: Space Harrier 3D (Sega, 1988)";
    harrierstats.SetText(stats_to_string.str());
    ////////////////////////////////////////////////////////////////////////////

    /*
     *If the Harrier moved, create a new line that tethers him to the center.
     *Sholudn't have to create a new object, but due to how sf::Shape works I
     *don't have many other options.  At least it works.
     */
    if (currentpos != VectorFloat(0, 0))
        centerline = Shape::Line(harrier.GetPosition(), center, 5, Color::White);
}

void ScalarVsVectorState::render()
{
    Window.Draw(bg          );
    Window.Draw(centerline  );
    Window.Draw(harrier     );
    Window.Draw(harrierstats);
    Window.Display();
}
