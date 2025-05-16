#include "PieceTable.h"

#include <filesystem>
#include <fstream>

#include "Cursor.h"

PieceTable::PieceTable(Cursor* cur, std::string path)
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

void PieceTable::insert(std::string string)
{

}

void PieceTable::delete_letter()
{

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
	row_starts[0] = 0;
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

PieceTable::TableRow* PieceTable::insert_row_after(TableRow* address, TableRow new_row)
{
	if (address == nullptr) {
		table.insert(table.begin(), new_row);
		return &table.front();
	}
	for (size_t i = 0; i < table.size(); i++) {
		if (&table[i] == address) {
			if (i < table.size() - 1) {
				table.insert(table.begin() + i + 1, new_row);
				return &table[i + 1];
			}
		}
	}
	return nullptr;
}
