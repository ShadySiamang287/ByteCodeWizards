#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Input
{
public:
	void setKeyDown(int key);
	void setKeyUp(int key);

	void setMousePosition(sf::Vector2i pos);
	void setLeftMouseDown();
	void setLeftMouseUp();
	void setRightMouseDown();
	void setRightMouseUp();

	bool isKeyDown(int key);
	bool isLeftMouseDown();
	bool isRightMouseDown();
	sf::Vector2i getMousePosition();

	bool isTyping();
	void setTyping(bool mode);
	
	void clearString();
	void appendString(char new_string);
	std::string getTypedString();

private:
	bool keys[256]{ false };

	bool typing{ false };
	std::string typed_string{ "" };

	struct Mouse {
		sf::Vector2i position;
		bool left, right{ false };
	};

	Mouse mouse;
};

