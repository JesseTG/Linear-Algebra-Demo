#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>
#include "Logger.h"

class State;
class TitleState;
class StateManager;


//Typedefs for less typing (the scope operator :: looks ugly)  /////////////////
typedef sf::Clock Clock;
typedef sf::Color Color;
typedef sf::Event Event;
typedef sf::Font Font;
typedef sf::Image Image;
typedef sf::Rect<float> RectFloat;
typedef sf::Rect<int> RectInt;
typedef sf::RenderWindow RenderWindow;
typedef sf::Vector2<int> VectorInt;
typedef sf::Vector2<float> VectorFloat;
typedef sf::Shape Shape;
typedef sf::Sprite Sprite;
typedef sf::String StringGraphic;
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

extern Event event;  //The object the latest event (external input) is stored in
extern Image sprites;  //The entire spritesheet.  All graphics taken from here.
extern Image bgimage;  //The background image.
extern Sprite bg;  //The sprite that represents this background image.
extern RenderWindow Window;
extern const VectorFloat center;
extern Logger logger;
extern StateManager StateController;


#endif //DECLARATIONS_H
