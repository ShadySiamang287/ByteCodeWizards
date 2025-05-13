#include "Input.h"

void Input::setKeyDown(int key)
{
	if (key >= 0) {
		keys[key] = true;
	}
}

void Input::setKeyUp(int key)
{
	if (key >= 0) {
		keys[key] = false;
	}
}

void Input::setMousePosition(sf::Vector2i pos)
{
	mouse.position = pos;
}

void Input::setLeftMouseDown()
{
	mouse.left = true;
}

void Input::setLeftMouseUp()
{
	mouse.left = false;
}

void Input::setRightMouseDown()
{
	mouse.right = true;
}

void Input::setRightMouseUp()
{
	mouse.right = false;
}

bool Input::isKeyDown(int key)
{
	if (key >= 0) {
		return keys[key];
	}
	return false;
}

bool Input::isLeftMouseDown()
{
	return mouse.left;
}

bool Input::isRightMouseDown()
{
	return mouse.right;
}

sf::Vector2i Input::getMousePosition()
{
	return mouse.position;
}

bool Input::isTyping()
{
	return typing;
}

void Input::setTyping(bool mode)
{
	typing = mode;
}

void Input::clearString()
{
	typed_string = "";
}

void Input::appendString(char new_string)
{
	if (int(new_string) < 32) {
		switch (int(new_string)) {
		case 13:
			typed_string += "\n";
			break;
		case 8:
			typed_string += new_string;
			break;
		}
	}
	else {
		typed_string += new_string;
	}
}

std::string Input::getTypedString()
{
	return typed_string;
}
