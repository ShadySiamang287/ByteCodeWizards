#pragma once
#include <SFML/Graphics.hpp>
#include "../Input.h"
#include "TextRenderer.h"
class TextEditor
{
private:
	sf::RenderWindow* window;
	Input* input;

	TextRenderer* text;

public:
	TextEditor(sf::RenderWindow* hwnd, Input* in);
	~TextEditor();
	void update(float dt);
	void handleInput(float dt);
	void render();
};

