#include "PieceTable.h"

#include "../GameObject.h"
#include "../Animation.h"

class Cursor : public GameObject {
public:
	Cursor(); 

	void handleInput(float dt) override;
	void update(float dt) override;

	void set_table(PieceTable* new_table);

	// string data && pos
	PieceTable::TableRow* get_row();
	void set_row(PieceTable::TableRow* new_row);

	int get_global_pos();
	void set_global_pos(int new_pos);

	int get_local_pos();
	void set_local_pos(int new_pos);

	// input handling
	void increase_line_number();
	void decrease_line_number();

	void increase_line_pos();
	void decrease_line_pos();

private:
	// string data && pos
	PieceTable::TableRow* row;
	PieceTable* table;

	int local_pos;
	int global_pos;

	// animation
	Animation blink;
	sf::Texture texture;

	// input handling
	bool old_up;
	bool old_down;
	bool old_left;
	bool old_right;

	int previous_line_pos;
	int line_pos;

	int line_number;
	int previous_line_number;
};