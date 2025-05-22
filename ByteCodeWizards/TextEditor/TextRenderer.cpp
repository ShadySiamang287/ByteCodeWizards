#include "TextRenderer.h"

#include "PieceTable.h"

TextRenderer::TextRenderer(Input* in, int width)
{
	input = in;
	input->setTyping(true);

	max_line_length = width / 24;

	cursor.setInput(input);
	table = new PieceTable(&cursor);
	cursor.set_table(table);
	cursor.setSize(sf::Vector2f(15.0f, 20.0f));
	cursor.setPosition(sf::Vector2f(1.0f, 5.0f));

	if (!font.openFromFile("font/mark_pro.otf")) {
		throw "Font failed to load to font!";
	}
	text = new sf::Text(font);
	text->setPosition(sf::Vector2f(0.0f, 0.0f));
	text->setCharacterSize(24);
}

TextRenderer::~TextRenderer()
{
	delete text;
	delete table;
}

void TextRenderer::update(float dt)
{
	cursor.update(dt);
	text->setString(table->resultant_string());
}

void TextRenderer::handleInput(float dt)
{
	std::string string = input->getTypedString();

	std::string::size_type found = string.find((char)8);
	if (std::string::npos != found)
	{
		table->delete_letter();
		string.erase(found);
	}

	if (string != "") {
		table->insert(string);
	}
}

void TextRenderer::render(sf::RenderWindow* hwnd)
{
	hwnd->draw(*text);
	hwnd->draw(cursor);
}
