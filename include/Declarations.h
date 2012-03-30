#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "Logger.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

class StateManager;
class State;
class TitleState;


typedef sf::Rect<float> RectFloat;
typedef sf::Vector2<int> VectorInt;
typedef sf::Vector2<float> VectorFloat;

enum class StateName : char {
  NADA = 0,
  TITLE,
  VECTORS,
  VECTORS_VS_SCALARS,
  RASTER_VS_VECTOR,
  MATRICES,
  TRANSLATION_DISTANCE_LENGTH,
  DOT_CROSS_PRODUCTS,
  REFLECTION,
  ROTATION,
  BAD_ROTATION,
  SHEARING,
  SCALING,
  PROJECTION,
  CONCLUSION
};

sf::Event event;
sf::Font font;
sf::Image bgimage;
sf::Sprite bg;


sf::RenderWindow Window(sf::VideoMode(640, 480, 32), "Linear Algebra Demo");
Logger logger;


#endif //DECLARATIONS_H
