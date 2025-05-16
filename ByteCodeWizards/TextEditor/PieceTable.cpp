#include "PieceTable.h"

#include <filesystem>
#include <fstream>

#include "Cursor.h"

PieceTable::PieceTable(std::string path, Cursor* cur)
{
	file_path = path;
	original = "";
	if (std::filesystem::exists(path)) {
		std::ifstream file(path);
		original = std::string((std::istreambuf_iterator<char>(file)),
								std::istreambuf_iterator<char>());
		file.close();
	}
	table.push_back(TableRow{ ORIGINAL, 0, (int)original.length()});
	add = "";
	table.push_back(TableRow{ ADD, 0, 0 });

	cursor = cur;
	cursor->set_row(&table.back());
}

PieceTable::PieceTable(Cursor* cur)
{
	original = "";
	table.push_back(TableRow{ ORIGINAL, 0, 0});
	add = "";
	table.push_back(TableRow{ ADD, 0, 0 });

	cursor = cur;
	cursor->set_row(&table.back());
}

void PieceTable::insert(int index, std::string string)
{
	if (index == total_length() - 1) {
		if (table.back().which == ADD){
			table.back().length += (int)string.length();
		}
		else {
			table.push_back(TableRow{ ADD, (int)add.length(), (int)string.length() });
		}
	}
	add += string;
}

void PieceTable::delete_letter(int index)
{
	if (index < 0 || index > total_length()) {
		return;
	}

	if (index == total_length() - 1) {
		if (table.back().length > 0) {
			table.back().length -= 1;
			table.push_back(TableRow{ ADD, (int)add.length(), 0 });
		}
		else if (table[table.size() - 2].length > 0) {
			table[table.size() - 2].length -= 1;
		}
	}
}

char PieceTable::index(int index)
{
	return 0;
}

std::string PieceTable::resultant_string()
{
	std::string string = "";

	for (TableRow row : table) {
		if (row.length > 0) {
			if (row.which == ORIGINAL && row.start < original.length()) {
				string += original.substr(row.start, row.length);
			}
			else if (row.which == ADD && row.start < add.length()) {
				string += add.substr(row.start, row.length);
			}
		}
	}

	return string;
}

int PieceTable::total_length()
{
	int length = 0;
	for (TableRow row : table) {
		length += row.length;
	}
	return length;
}

void PieceTable::set_file_path(std::string path)
{

	file_path = path;
}

void PieceTable::save()
{
	std::ofstream file(file_path);
	file << resultant_string();
	file.close();
}

PieceTable::TableRow* PieceTable::get_row_of_index(int letter_index)
{
	if (letter_index < 0 || letter_index >= total_length()) {
		return nullptr;
	}

	// get the starting point of all rows
	std::vector<int> row_starts(table.size(), 0);
	for (size_t i = 0; i < table.size(); i++) {
		row_starts[i] = row_starts[i - 1] + table[i - 1].length;
	}

	int left = 0;
	int right = (int)table.size() - 1;

	// binary search using the starting point of all rows + end their point
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int row_start = row_starts[mid];
		int row_end = row_start + table[mid].length - 1;
		
		if (letter_index < row_start) {
			right = mid - 1;
		}
		else if (letter_index > row_end) {
			left = mid + 1;
		}
		else {
			return &table[mid];
		}
	}

	return nullptr;
}
