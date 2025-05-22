#include "TextEditor.h"

#include "PieceTable.h"

TextEditor::TextEditor(Input* in, int width)
{
	input = in;
	input->setTyping(true);

	max_line_length = width / 24;

	table = new PieceTable(&cursor);

	cursor.setInput(input);
	cursor.set_table(table);
	cursor.setSize(sf::Vector2f(15.0f, 20.0f));
	cursor.setPosition(sf::Vector2f(1.0f, 5.0f));

	if (!font.openFromFile("font/Consolas.ttf")) {
		throw "Font failed to load to font!";
	}
	text = new sf::Text(font);
	text->setPosition(sf::Vector2f(0.0f, 0.0f));
	text->setCharacterSize(24);
}

TextEditor::~TextEditor()
{
	delete text;
	delete table;
}

void TextEditor::update(float dt)
{
	cursor.update(dt);
	text->setString(table->resultant_string());
}

void TextEditor::handleInput(float dt)
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

	cursor.handleInput(dt);
}

void TextEditor::render(sf::RenderWindow* hwnd)
{
	hwnd->draw(*text);
	hwnd->draw(cursor);
}
