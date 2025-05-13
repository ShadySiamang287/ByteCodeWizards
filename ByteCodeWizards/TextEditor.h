#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
class TextEditor
{
private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text text{ font };

	Input* input;
	std::string string;

public:
	TextEditor(sf::RenderWindow* hwnd, Input* in);
	~TextEditor();
	void update(float dt);
	void handleInput(float dt);
	void render();
};

