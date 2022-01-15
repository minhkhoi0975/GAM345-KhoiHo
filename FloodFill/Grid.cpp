#include "Grid.h"

Grid::Grid(std::vector<std::vector<int>>& values): values(values), width(values.size()), height(values.size() < 1 ? 0 : values[0].size())
{
}

Grid::Grid(std::vector<std::vector<int>>&& values): values(values), width(values.size()), height(values.size() < 1 ? 0 : values[0].size())
{
}

int Grid::GetWidth() const
{
	return width;
}

int Grid::GetHeight() const
{
	return height;
}

bool Grid::isIndexValid(const int& row, const int& column) const
{
	// Check if the row is valid.
	if (row < 0)
		return false;
	if (row >= width)
		return false;

	// Check if the column is valid.
	if (column < 0)
		return false;
	if (column >= height)
		return false;

	return true;
}

int Grid::GetValueAt(const int& row, const int& column) const
{
	return values[row][column];
}

const std::vector<int>& Grid::GetValuesAtRow(const int& row) const
{
	return values[row];
}

std::vector<int> Grid::GetValuesAtColumn(const int& column) const
{
	std::vector<int> columnValues;
	columnValues.reserve(values.size());

	for (int i = 0; i < columnValues.capacity(); i++)
	{
		columnValues.push_back(values[i][column]);
	}

	return columnValues;
}

void Grid::SetValue(const int& row, const int& column, const int& newValue)
{
	values[row][column] = newValue;
}
