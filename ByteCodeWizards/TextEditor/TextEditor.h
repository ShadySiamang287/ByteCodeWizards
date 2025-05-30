#pragma once
#include "../Input.h"
#include <SFML/Graphics.hpp>
#include "Cursor.h"

class PieceTable;

class TextEditor
{
public:
	TextEditor(Input* in, int width);
	~TextEditor();

	void update(float dt);
	void handleInput(float dt);
	void render(sf::RenderWindow* hwnd);

private:
	int max_line_length;
	Input* input;

	PieceTable* table;
	Cursor cursor;

	sf::Text* text;
	sf::Font font;
};

