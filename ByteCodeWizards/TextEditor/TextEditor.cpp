#include "TextEditor.h"

TextEditor::TextEditor(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	window->setKeyRepeatEnabled(false);
	text = new TextRenderer(in, hwnd->getSize().x);
}

TextEditor::~TextEditor() 
{
	input->setTyping(false);
}

void TextEditor::update(float dt) 
{
	text->update(dt);
}

void TextEditor::handleInput(float dt)
{
	text->handleInput(dt);
}

void TextEditor::render()
{
	window->clear(sf::Color::Blue);
	text->render(window);
	window->display();
}
