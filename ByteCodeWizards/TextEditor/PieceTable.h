#pragma once
#include <vector>
#include <string>

class Cursor;

class PieceTable
{
public:
	PieceTable(std::string path, Cursor* cur);
	PieceTable(Cursor* cur);

	void insert(int index, std::string string);
	void delete_letter(int index);

	char index(int index);
	std::string resultant_string();

	int total_length();

	void set_file_path(std::string path);
	void save();

private:
	enum type {
		ORIGINAL,
		ADD,
	};

public:
	struct TableRow {
		type which;
		int start;
		int length;
	};

private:
	TableRow * get_row_of_index(int letter_index);

	std::vector<TableRow> table;
	std::string original;
	std::string add;

	std::string file_path;

	Cursor* cursor;
};

