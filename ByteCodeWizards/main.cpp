#include <SFML/Graphics.hpp>
#include "TextEditor.h"
#include "Input.h"

#include <windows.h>

void windowProcess(sf::RenderWindow* window, Input* input) {
    input->clearString();
    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
        else if (const auto* resize = event->getIf<sf::Event::Resized>()) {
            window->setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { (float)resize->size.x, (float)resize->size.y })));
        }
        else if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
            input->setKeyDown(static_cast<int>(keyPress->code));
        }
        else if (const auto* keyPress = event->getIf<sf::Event::KeyReleased>()) {
            input->setKeyUp(static_cast<int>(keyPress->code));
        }
        else if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
        {
            if (input->isTyping()) {
                if (textEntered->unicode < 128) {
                    input->appendString(static_cast<char>(textEntered->unicode));
                }
            }
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButtonPressed->button == sf::Mouse::Button::Right)
            {
                input->setRightMouseDown();
            } 
            else if (mouseButtonPressed->button == sf::Mouse::Button::Right)
            {
                input->setLeftMouseDown();
            }
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseButtonPressed->button == sf::Mouse::Button::Right)
            {
                input->setRightMouseUp();
            }
            else if (mouseButtonPressed->button == sf::Mouse::Button::Right)
            {
                input->setLeftMouseUp();
            }
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            input->setMousePosition(mouseMoved->position);
        }
    }
}

int main()
{   
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Bytecode wizards!");
    Input input;
    
    TextEditor level = TextEditor(&window, &input);
    
    sf::Clock clock;
    float deltaTime;
    while (window.isOpen())
    {
        windowProcess(&window, &input);
        deltaTime = (float)clock.restart().asMilliseconds();

        level.handleInput(deltaTime);
        level.update(deltaTime);
        level.render();
    }
}