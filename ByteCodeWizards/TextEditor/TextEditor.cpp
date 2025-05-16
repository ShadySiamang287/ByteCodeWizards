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

void TextEditor::handleInput(float dt){
	//string += input->getTypedString();

	//std::string::size_type found = string.find((char)8);
	//if (std::string::npos != found)
	//{
	//	if (found > 0 && (int)string.length() >= 2) {
	//		string.erase(found - 1, found);
	//	}
	//	else {
	//		string.erase(found);
	//	}
	//}
	text->handleInput(dt);
}

void TextEditor::render()
{
	window->clear(sf::Color::Blue);
	text->render(window);
	window->display();
}
