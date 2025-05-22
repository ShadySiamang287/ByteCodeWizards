#include "SpellEditor.h"

SpellEditor::SpellEditor(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	window->setKeyRepeatEnabled(false);
	text = new TextEditor(in, hwnd->getSize().x);
}

SpellEditor::~SpellEditor() 
{
	input->setTyping(false);
}

void SpellEditor::update(float dt) 
{
	text->update(dt);
}

void SpellEditor::handleInput(float dt)
{
	text->handleInput(dt);
}

void SpellEditor::render()
{
	window->clear(sf::Color::Blue);
	text->render(window);
	window->display();
}
