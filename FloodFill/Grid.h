#pragma once

#include <vector>

class Grid
{
private:
	int sizeX;
	int sizeY;
	std::vector<std::vector<int>> values;

public:
	Grid(std::vector<std::vector<int>> & values);
	Grid(std::vector<std::vector<int>> && arr);

	// Get size X of the grid.
	int GetSizeX() const;

	// Get size Y of the grid.
	int GetSizeY() const;

	// Check if the index valid.
	bool isIndexValid(const int& xPos, const int& yPos) const;

    // Get the value at an index.
	int GetValueAt(const int& xPos, const int& yPos) const;

	// Get all values at x position.
	const std::vector<int>& GetValuesAtXPos(const int& xPos) const;

	// Get all values at y position.
	std::vector<int> GetValuesAtYPos(const int& yPos) const;

	// Set the value at an index.
	void SetValue(const int& xPos, const int& yPos, const int& newValue);
};