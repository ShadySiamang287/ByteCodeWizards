#include "Cursor.h"

Cursor::Cursor()
{
	row = nullptr;
	local_pos = 0;
	global_pos = 0;
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
