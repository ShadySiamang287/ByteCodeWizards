#pragma once
#include <SFML/Graphics.hpp>
#include "../Input.h"
#include "TextEditor.h"
class SpellEditor
{
private:
	sf::RenderWindow* window;
	Input* input;

	TextEditor* text;

public:
	SpellEditor(sf::RenderWindow* hwnd, Input* in);
	~SpellEditor();
	void update(float dt);
	void handleInput(float dt);
	void render();
};

