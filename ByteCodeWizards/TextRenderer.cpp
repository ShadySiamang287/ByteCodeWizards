#include "TextRenderer.h"

#include "PieceTable.h"
#include "Input.h"

TextRenderer::TextRenderer(Input* in, int width)
{
	input = in;
	input->setTyping(true);

	max_line_length = width / 24;

	table = new PieceTable();

	if (!font.openFromFile("font/mark_pro.otf")) {
		throw "Font failed to load to font!";
	}
	text = new sf::Text(font);
	text->setPosition(sf::Vector2f(0.0f, 0.0f));
}

TextRenderer::~TextRenderer()
{
	delete text;
	delete table;
}

void TextRenderer::update(float dt)
{
	text->setString(table->resultant_string());
}

void TextRenderer::handleInput(float dt)
{
	std::string string = input->getTypedString();

	std::string::size_type found = string.find((char)8);
	if (std::string::npos != found)
	{
		table->delete_letter(table->total_length() - 1);
		string.erase(found);
	}

	if (string != "") {
		table->insert(table->total_length() - 1, string);
	}
}

void TextRenderer::render(sf::RenderWindow* hwnd)
{
	hwnd->draw(*text);
}
