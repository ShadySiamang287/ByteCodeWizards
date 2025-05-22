#include <SFML/Graphics.hpp>

#include "TextEditor/TextEditor.h"
#include "Input.h"

#include <windows.h>

const float MS_PER_UPDATE = 1000.0f / 60.0f;

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
    float previous = (float)clock.restart().asMilliseconds();
    float lag = 0.0f;
    while (window.isOpen())
    {
        windowProcess(&window, &input);

        float current = clock.getElapsedTime().asMilliseconds();
        float deltaTime = current - previous;
        previous = current;
        lag += deltaTime;

        level.handleInput(deltaTime);

        while (lag >= MS_PER_UPDATE){
            level.update(deltaTime);
            lag -= MS_PER_UPDATE;
        }
        level.render();
    }
}