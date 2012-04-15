#include "../include/State.h"

//I don't want to put these tiny methods in a separate file, but if I don't
//the linker gives me errors.

State::State()
{ setNextState(StateName::NADA); }

StateName State::getNextState() const
{ return this->nextstate; }

void State::setNextState(const StateName newnextstate)
{ this->nextstate = newnextstate; }

void State::checkForNextState(const StateName prev, const StateName next)
{
    while (Window.GetEvent(event)) {
        if (event.Type == sf::Event::KeyPressed) {
            if (event.Key.Code == sf::Key::O) setNextState(prev);
            else if (event.Key.Code == sf::Key::P) setNextState(next);
        }
    }
}
