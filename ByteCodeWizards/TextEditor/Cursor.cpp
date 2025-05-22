#include "Cursor.h"
#include <iostream>

Cursor::Cursor()
{
	table = nullptr;
	row = nullptr;
	local_pos = 0;
	global_pos = 0;

	line_number = 0;
	previous_line_number = 0;

	previous_line_pos = 0;
	line_pos = 0;

	blink.addFrame(sf::IntRect({ 0, 0 }, { 15, 24 }));
	blink.addFrame(sf::IntRect({ 15, 0 }, { 15, 24 }));
	blink.setLooping(true);
	blink.setFrameSpeed(30.0f);

	if (!texture.loadFromFile("./GFX/cursor.png")) {
		throw "Failed to load cursor.png";
	}
	setTexture(&texture);

	old_up = false;
	old_down = false;
	old_left = false;
	old_right = false;
}

void Cursor::handleInput(float dt)
{
	bool left = input->isKeyDown((int)sf::Keyboard::Key::Left);
	bool right = input->isKeyDown((int)sf::Keyboard::Key::Right);
	bool up = input->isKeyDown((int)sf::Keyboard::Key::Up);
	bool down = input->isKeyDown((int)sf::Keyboard::Key::Down);


	if (left && (left != old_left)) {
		decrease_line_pos();
	}
	else if (right && (right != old_right)) {
		increase_line_pos();
	}
	else if (up && (up != old_up)) {
		decrease_line_number();
	}
	else if (down && (down != old_down)) {
		increase_line_number();
	}

	old_left = left;
	old_right = right;
	old_up = up;
	old_down = down;
}

void Cursor::update(float dt)
{
	if (previous_line_pos != line_pos) {
		if (previous_line_pos < line_pos) {
			move(sf::Vector2f(13.2f, 0.0f));
		}
		else {
			move(sf::Vector2f(-13.2f, 0.0f));
		}
	}

	if (line_number != previous_line_number) {
		if (previous_line_number < line_number) {
			move(sf::Vector2f(0.0f, 29.0f));
		}
		else {
			move(sf::Vector2f(0.0f, -29.0f));
		}
	}

	if (line_pos == 0) {
		setPosition(sf::Vector2f(1.0f, getPosition().y));
	}

	if (line_number == 0) {
		setPosition(sf::Vector2f(getPosition().x, 5.0f));
	}

	previous_line_pos = line_pos;
	previous_line_number = line_number;

	blink.animate(dt);
	setTextureRect(blink.getCurrentFrame());
}

PieceTable::TableRow* Cursor::get_row()
{
	return row;
}

void Cursor::set_row(PieceTable::TableRow* new_row)
{
	row = new_row;
}

int Cursor::get_global_pos()
{
	return global_pos;
}

void Cursor::set_global_pos(int new_pos)
{
	global_pos = new_pos;
}

int Cursor::get_local_pos()
{
	return local_pos;
}

void Cursor::set_local_pos(int new_pos)
{
	local_pos = new_pos;
}

void Cursor::set_table(PieceTable* new_table)
{
	table = new_table;
}

void Cursor::increase_line_number()
{
	++line_number;
	line_pos = 0;
}

void Cursor::decrease_line_number()
{
	if (line_number > 0) {
		--line_number;
		line_pos = 0;
	}
}

void Cursor::increase_line_pos()
{
	++line_pos;
}

void Cursor::decrease_line_pos()
{
	if (line_pos > 0) {
		--line_pos;
	}
	else {
		line_pos = 0;
	}
}
