#pragma once
#include <vector>
#include <string>

class PieceTable
{
public:
	PieceTable(std::string path);
	PieceTable();

	void insert(int index, std::string string);

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

	struct table_row {
		type which;
		int start;
		int length;
	};

	std::vector<table_row> table;
	std::string original;
	std::string add;

	std::string file_path;
};

