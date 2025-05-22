#include "PieceTable.h"

#include "../GameObject.h"
#include "../Animation.h"

class Cursor : public GameObject {
public:
	Cursor(); 

	void handleInput(float dt) override;
	void update(float dt) override;

	PieceTable::TableRow* get_row();
	void set_row(PieceTable::TableRow* new_row);

	int get_global_pos();
	void set_global_pos(int new_pos);

	int get_local_pos();
	void set_local_pos(int new_pos);

	void set_table(PieceTable* new_table);

private:
	PieceTable::TableRow* row;
	PieceTable* table;
	int	previous_local_pos;
	int previous_global_pos;
	int local_pos;
	int global_pos;

	Animation blink;
	sf::Texture texture;
};