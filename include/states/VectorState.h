#ifndef VECTORSTATE_H
#define VECTORSTATE_H

#include "../Declarations.h"
#include "../State.h"

#include <iostream>


class VectorState : public State
{
    public:
        VectorState();
        virtual ~VectorState() {}

        void input();
        void logic();
        void render();

    private:
};

VectorState::VectorState()
{
    logger.log("Entering Vectors state.");

    setNextState(StateName::NADA);
}

void VectorState::input()
{
    while (Window.GetEvent(event)) {
        if (event.Type == sf::Event::KeyPressed) {
            if (event.Key.Code == sf::Key::O)
                setNextState(StateName::TITLE);
            else if (event.Key.Code == sf::Key::P)
                setNextState(StateName::NADA);
        }
    }
}

void VectorState::logic()
{

}

void VectorState::render()
{
    Window.Draw(bg);
    Window.Display();
}

#endif // VECTORSTATE_H
