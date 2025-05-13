#include "PieceTable.h"

#include <filesystem>
#include <fstream>

PieceTable::PieceTable(std::string path)
{
	file_path = path;
	if (std::filesystem::exists(path)) {
		std::ifstream file(path);
		original = std::string((std::istreambuf_iterator<char>(file)),
								std::istreambuf_iterator<char>());
		file.close();
	}
	add = "";
}

PieceTable::PieceTable()
{
	original = "";
	add = "";
}

void PieceTable::insert(int index, std::string string)
{
	add += string;
	if (index == total_length() - 1) {
		table.back().length += string.length();
	}
}

char PieceTable::index(int index)
{
	return 0;
}

std::string PieceTable::resultant_string()
{
	std::string string = "";
	return std::string();
}

int PieceTable::total_length()
{
	int length = 0;
	for (table_row row : table) {
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
