#pragma once
#include <SFML/Graphics.hpp>

class Input;
class PieceTable;

class TextRenderer
{
public:
	TextRenderer(Input* in);
	~TextRenderer();

	void update(float dt);
	void handleInput(float dt);
	void render(sf::RenderWindow* hwnd);

private:
	Input* input;
	PieceTable* table;

	sf::Text* text;
	sf::Font font;
};

