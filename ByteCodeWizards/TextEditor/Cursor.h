#include "PieceTable.h"
#include "../GameObject.h"

class Cursor : public GameObject {
public:
	Cursor(); 

	PieceTable::TableRow* get_row();
	void set_row(PieceTable::TableRow* new_row);

	int get_global_pos();
	void set_global_pos(int new_pos);

	int get_local_pos();
	void set_local_pos(int new_pos);

private:
	PieceTable::TableRow* row;
	int local_pos;
	int global_pos;
};