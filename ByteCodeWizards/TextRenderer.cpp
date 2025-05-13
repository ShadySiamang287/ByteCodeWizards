#include "TextRenderer.h"

#include "PieceTable.h"
#include "Input.h"

TextRenderer::TextRenderer(Input* in)
{
	input = in;
	input->setTyping(true);

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
		if (found > 0 && (int)string.length() >= 2) {
			string.erase(found - 1, found);
		}
		else {
			string.erase(found);
		}
	}
}

void TextRenderer::render(sf::RenderWindow* hwnd)
{
	hwnd->draw(*text);
}
