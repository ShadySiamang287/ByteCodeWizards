#pragma once
#include <vector>
#include <string>

class Cursor;

class PieceTable
{
public:
	PieceTable(Cursor* cur);
	PieceTable(Cursor* cur, std::string path);

	void insert(std::string string);
	void delete_letter();

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
		bool operator==(const TableRow& other) const {
			return which == other.which && start == other.start && length == other.length;
		}
	};

private:
	TableRow* get_row_of_index(int letter_index);
	TableRow* insert_row_after(TableRow* address, TableRow new_row);

	std::vector<TableRow> table;
	std::string original;
	std::string add;

	std::string file_path;

	Cursor* cursor;
};

