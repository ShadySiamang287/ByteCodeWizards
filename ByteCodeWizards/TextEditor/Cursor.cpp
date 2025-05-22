#include "Cursor.h"

Cursor::Cursor()
{
	table = nullptr;
	row = nullptr;
	local_pos = 0;
	global_pos = 0;

	blink.addFrame(sf::IntRect({ 0, 0 }, { 15, 24 }));
	blink.addFrame(sf::IntRect({ 15, 0 }, { 15, 24 }));
	blink.setLooping(true);
	blink.setFrameSpeed(30.0f);

	if (!texture.loadFromFile("./GFX/cursor.png")) {
		throw "Failed to load cursor.png";
	}
	setTexture(&texture);
}

void Cursor::handleInput(float dt)
{
	if (local_pos > row->length) {

	}
}

void Cursor::update(float dt)
{
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
