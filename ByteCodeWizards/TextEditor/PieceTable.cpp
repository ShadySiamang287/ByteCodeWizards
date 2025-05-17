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
	int local_pos = cursor->get_local_pos();
	int global_pos = cursor->get_global_pos();
	TableRow* current_row = cursor->get_row();
	// nullptr check
	if (current_row == nullptr) {
		cursor->set_row(&table.back());
		current_row = &table.back();
	}

	// if the current row is using the original string
	if (current_row->which == ORIGINAL) {
		TableRow* new_row = insert_row_after(current_row, TableRow{ ADD, (int)add.length(), 1 });

		cursor->set_local_pos(1);
		cursor->set_row(new_row);
	}
	// if the current row being inserted into is the end of the string addition string
	else if (current_row->start == (add.length() - current_row->length)) {
		++current_row->length;
		cursor->set_local_pos(++local_pos);
	}
	// any other string;
	else {
		// calc the difference in rows
		int difference = current_row->length - local_pos;
		
		current_row->length = local_pos;
		TableRow* new_row = insert_row_after(current_row, TableRow{ ADD, (int)add.length(), 1 });
		insert_row_after(new_row, TableRow{ ADD, current_row->start + difference, difference });

		cursor->set_local_pos(1);
		cursor->set_row(new_row);
	}

	add += string;
	cursor->set_global_pos(++global_pos);
}

void PieceTable::delete_letter()
{
	int local_pos = cursor->get_local_pos();
	int global_pos = cursor->get_global_pos();
	TableRow* current_row = cursor->get_row();

	// only at local_pos 0 if the row is empty
	if (local_pos == 0) {
		auto table_pos = std::find(table.begin(), table.end(), *current_row);
		if (table_pos != table.end() && table_pos != table.begin()) {
			size_t index = std::distance(table.begin(), table_pos);
			cursor->set_row(&table[index - 1]);
			table.erase(table_pos);
		}
	}
	else if (current_row->length > 0) {
		current_row->length -= 1;
	}

	if (local_pos > 0){
		cursor->set_local_pos(--local_pos);
	}

	if (global_pos > 0) {
		cursor->set_global_pos(--global_pos);
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
	
	table.push_back(new_row);
	return &table.back();
}
