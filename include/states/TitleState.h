#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "../Declarations.h"
#include "../State.h"

/*
 * This is my project's title screen.  It features only a rotating sprite and
 * some information off to the sides.
 */

/*
 * This is a class, aka a blueprint for a type of data.  It's a sort of black box
 * that abstracts away certain processes so we can describe solutions in terms of
 * the problem.
 */
class TitleState : public State
{
  public:
    TitleState();
    ~TitleState();

    void input();
    void logic();
    void render() const;

  private:
    Sprite mario;
    StringGraphic title;
};

/*
   I really do think you should learn to code, Mr. Ski, as a math teacher
   there's so much you could do after spending a summer learning how to use
   Octave or Maxima (both of which are free).
 */

#endif //TITLESTATE_H
