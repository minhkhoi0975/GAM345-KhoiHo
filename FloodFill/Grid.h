#pragma once

#include <vector>

class Grid
{
private:
	int width;
	int height;
	std::vector<std::vector<int>> values;

public:
	Grid(std::vector<std::vector<int>> & values);
	Grid(std::vector<std::vector<int>> && arr);

	// Get the width of the grid.
	int GetWidth() const;

	// Get the height of the grid.
	int GetHeight() const;

	// Check if the index valid.
	bool isIndexValid(const int& row, const int& column) const;

    // Get the value at an index.
	// 0 <= row < width
	// 0 <= column < height
	int GetValueAt(const int& row, const int& column) const;

	// Get all the values on a row.
	// 0 <= row < width
	const std::vector<int>& GetValuesAtRow(const int& row) const;

	// Get all the values on a column.
	// 0 <= column < height
	std::vector<int> GetValuesAtColumn(const int& column) const;

	// Set the value at an index.
	void SetValue(const int& row, const int& column, const int& newValue);
};