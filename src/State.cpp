#include "../include/State.h"

State::State()
{ setNextState(StateName::NADA); }

StateName State::getNextState() const
{ return this->nextstate; }

void State::setNextState(const StateName newnextstate)
{ this->nextstate = newnextstate; }

void State::checkForNextState(const StateName prev, const StateName next)
{
    while (Window.GetEvent(event)) {                //While we're getting external input...
        if (event.Type == sf::Event::KeyPressed) {  //If a key was pressed...
            if (event.Key.Code == sf::Key::O)       //If that key was O...
                setNextState(prev);
            else if (event.Key.Code == sf::Key::P)  //Else if it was P...
                setNextState(next);
        }
    }
}
