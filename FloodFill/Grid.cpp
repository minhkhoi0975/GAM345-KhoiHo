#include "Grid.h"

Grid::Grid(std::vector<std::vector<int>>& values): values(values), sizeX(values.size()), sizeY(values.size() < 1 ? 0 : values[0].size())
{
}

Grid::Grid(std::vector<std::vector<int>>&& values): values(values), sizeX(values.size()), sizeY(values.size() < 1 ? 0 : values[0].size())
{
}

int Grid::GetSizeX() const
{
	return sizeX;
}

int Grid::GetSizeY() const
{
	return sizeY;
}

bool Grid::isIndexValid(const int& xPos, const int& yPos) const
{
	// Check if the row is valid.
	if (xPos < 0)
		return false;
	if (xPos >= sizeX)
		return false;

	// Check if the column is valid.
	if (yPos < 0)
		return false;
	if (yPos >= sizeY)
		return false;

	return true;
}

int Grid::GetValueAt(const int& xPos, const int& yPos) const
{
	return values[xPos][yPos];
}

const std::vector<int>& Grid::GetValuesAtXPos(const int& xPos) const
{
	return values[xPos];
}

std::vector<int> Grid::GetValuesAtYPos(const int& yPos) const
{
	std::vector<int> xPosValues;
	xPosValues.reserve(values.size());

	for (int i = 0; i < xPosValues.capacity(); i++)
	{
		xPosValues.push_back(values[i][yPos]);
	}

	return xPosValues;
}

void Grid::SetValue(const int& xPos, const int& yPos, const int& newValue)
{
	values[xPos][yPos] = newValue;
}
