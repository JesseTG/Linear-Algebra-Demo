#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "Logger.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>

class StateManager;
class State;
class TitleState;

//Typedefs for less typing (the scope operator :: looks ugly)  /////////////////
typedef sf::Color Color;
typedef sf::Rect<float> RectFloat;
typedef sf::Rect<int> RectInt;
typedef sf::Vector2<int> VectorInt;
typedef sf::Vector2<float> VectorFloat;
typedef sf::Sprite Sprite;
typedef sf::Shape Shape;
////////////////////////////////////////////////////////////////////////////////

//It's easy to interchange regular enumerations with integers.
enum Direction { UP, DOWN, LEFT, RIGHT };

//Enum classes, on the other hand, force you to do so explicitly.
enum class StateName : char {
  NADA = 0,
  TITLE,
  VECTORS,
  SCALARS_VS_VECTORS,
  RASTER_VS_VECTOR,
  MATRICES,
  TRANSLATION_DISTANCE_LENGTH,
  DOT_CROSS_PRODUCTS,
  REFLECTION,
  ROTATION,
  SCALING,
  CONCLUSION
};

sf::Event event;  //The object the latest event (external input) is stored in
sf::Image sprites;  //The entire spritesheet.  All graphics taken from here.
sf::Image bgimage;  //The background image.
Sprite bg;  //The sprite that represents this background image.


sf::RenderWindow Window(sf::VideoMode(640, 480, 32), "Linear Algebra Demo",
                        sf::Style::Titlebar | sf::Style::Close);
const VectorFloat center = VectorFloat(Window.GetWidth()/2, Window.GetHeight()/2);
Logger logger;


#endif //DECLARATIONS_H
