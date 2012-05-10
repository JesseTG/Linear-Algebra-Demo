#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define INPUT Window.GetInput()
#define MOUSE VectorFloat(INPUT.GetMouseX(), INPUT.GetMouseY())

#define IN_RANGE(num, min, max) (((min) <= (num)) && ((num) <= (max)))

#include <array>         //A data structure we use to store frames by number
#include <iomanip>       //Manipulates how I/O streams represent data
#include <memory>        //For smart pointers
#include <stdexcept>     //For exceptions
#include <sstream>       //To easily place numbers inside text
#include <unordered_map> //A data structure we use to store frames by name

#include <boost/lexical_cast.hpp>  //So we can report state IDs if an error is thrown

#include <SFML/Graphics.hpp>  //The graphics library; vital to this project!
#include <SFML/Audio.hpp>     //The sound library that's also used

//The class forward declarations.
class State       ;
class TitleState  ;
class StateManager;

//Typedefs for less typing (the scope operator :: looks ugly)  /////////////////
typedef sf::Clock          Timer;
typedef sf::Color          Color;
typedef sf::Event          Event;
typedef sf::Font           Font;
typedef sf::Image          Image;
typedef sf::Input          Input;
typedef sf::Randomizer     Random;
typedef sf::Rect<float>    RectFloat;
typedef sf::Rect<int>      RectInt;
typedef sf::RenderWindow   RenderWindow;
typedef sf::Vector2<int>   VectorInt;
typedef sf::Vector2<float> VectorFloat;
typedef sf::Shape          Shape;
typedef sf::Sound          SoundEffect;
typedef sf::SoundBuffer    SoundFile;
typedef sf::Sprite         Sprite;
typedef sf::String         StringGraphic;
typedef sf::VideoMode      VideoMode;
////////////////////////////////////////////////////////////////////////////////

//It's easy to interchange regular enumerations with integers.
enum Direction { UP, DOWN, LEFT, RIGHT };

//Enum classes, on the other hand, force you to do so explicitly.
//The states available in this program
enum class StateName : char {
  NADA = 0          ,
  TITLE             ,
  VECTORS           ,
  SCALARS_VS_VECTORS,
  RASTER_VS_VECTOR  ,
  MATRICES          ,
  TRANSLATION       ,
  DOT_PRODUCTS      ,
  ROTATION          ,
  DUCKHUNT_TITLE    ,
  DUCKHUNT_GAME     ,
};

//A structure that holds sound, so we can juggle one object rather than two
struct Sound {
    SoundFile   file ;
    SoundEffect sound;
    void Play() { sound.Play(); }
    void Stop() { sound.Stop(); }
};

extern Image        bgimage;  //The background image.
extern Sprite       bg     ;  //The sprite that represents the background image.
extern Event        event  ;  //The latest external input is stored in
extern Image        sprites;  //The spritesheet file.  Most gfx come from here.
extern RenderWindow Window ;  //The window we actually see

extern StateManager StateController;

extern const VectorFloat CENTER;  //The center of the screen
extern const RectInt     SCREEN;  //The rectangle that comprises the screen

//Moves the sprite in question.
auto inputmove = [](const int speed, const bool ismoving[4],
                    sf::Sprite& sprite, const float buffer[4]) {
    sprite.Move(0, -speed * ismoving[UP] * (sprite.GetPosition().y > buffer[UP]));
    sprite.Move(0, speed * ismoving[DOWN] * (sprite.GetPosition().y < buffer[DOWN]));
    sprite.Move(-speed * ismoving[LEFT] * (sprite.GetPosition().x > buffer[LEFT]), 0);
    sprite.Move(speed * ismoving[RIGHT] * (sprite.GetPosition().x < buffer[RIGHT]), 0);
};

//Ensures that a sprite stops at the edge of the screen
auto setSpriteBuffer = [&SCREEN](const Sprite& sprite, float buffer[4]) {
    buffer[UP   ] = sprite.GetSize().y/2;
    buffer[DOWN ] = SCREEN.GetHeight() - buffer[UP];
    buffer[LEFT ] = sprite.GetSize().x/2;
    buffer[RIGHT] = SCREEN.GetWidth() - buffer[LEFT];
};

auto initSprite = [](Sprite& sprite, const Image& image, const RectInt& subrect,
                     const float scale, const VectorFloat& position = CENTER) {
    sprite.SetImage(image);
    sprite.SetSubRect(subrect);
    sprite.SetScale(scale, scale);
    sprite.SetCenter(subrect.GetWidth()/2, subrect.GetHeight()/2);
    sprite.SetPosition(position);
};

#endif //DECLARATIONS_H
