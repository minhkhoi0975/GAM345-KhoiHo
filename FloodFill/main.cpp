#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <utility>
#include <chrono>
#include <list>
#include <ctime>
#include <cstdlib>
#include <random>
#include <Windows.h>
#include "Grid.h"

// Print the values of a grid.
void PrintGrid(const Grid& grid, const std::pair<int, int>& startingPosition = std::pair<int, int>(-1, -1));

// Generate a grid whose size is NxN.
Grid GenerateGrid(const int& n);

// Get a random integer.
int GetRandomInteger(int minInclusive, int maxInclusive);

// Randomly replace some elements in a grid with the specfic value.
void RandomlySetValue(Grid& grid, const int& newValue, int elementsToReplace = 1);

// Randomly get a cell in the grid that does not match the specified value.
std::pair<int, int> GetRandomStartingCell(const Grid& grid, const int& valueToIgnore);

// Flood fill the grid from the center.
void FloodFillRecursive(Grid& grid, const int& row, const int& column, const int& value);
void FloodFillIterative(Grid& grid, const int& row, const int& column, const int& value);

// Generate a data file. Return true if the file is successfully generated.
bool GenerateDataFile(const std::string& dataFileName, const int &minN, const int &maxN);

// Generate a script file. Return true if the file is successfully generated.
bool GenerateScriptFile(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName);

// Test floodfill output.
void TestFloodFillOutput();

int main()
{
	TestFloodFillOutput();
	
	/*
	// Generate the data file.
	GenerateDataFile("my_data.txt", 10, 250);

	// Generate the script file.
	GenerateScriptFile("my_script.txt", "my_data.txt", "my_output.png");

	// Run gnuplot.
	system("gnuplot.exe my_script.txt");
	*/
}

void PrintGrid(const Grid& grid, const std::pair<int, int> & startingPosition)
{
	std::cout << std::endl;

	for (int column = 0; column < grid.GetSizeX(); column++)
	{
		for(int row = 0; row < grid.GetSizeY(); row++)
		{
			// yellow for starting position, white for 0, red for 1, green for any other number.
			int value = grid.GetValueAt(row, column);

			if (row == startingPosition.first && column == startingPosition.second)
				std::cout << "\033[96m";
			else if (value == 0)
				std::cout << "\033[39m";
			else if (value == 1)
				std::cout << "\033[31m";
			else
				std::cout << "\033[32m";

			std::cout << grid.GetValueAt(row, column) << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// Reset the color.
	std::cout << "\033[39m";
}

void FloodFillRecursive(Grid& grid, const int& row, const int& column, const int& value)
{
	// Stop filling if the currentcell is invalid or already filled.
	if (!grid.isIndexValid(row, column) || grid.GetValueAt(row, column) == 1 || grid.GetValueAt(row, column) == value)
		return;

	// Fill the current cell.
	grid.SetValue(row, column, value);
	
	// Fill the surrounding cells.
	FloodFillRecursive(grid, row - 1, column, value);
	FloodFillRecursive(grid, row, column - 1, value);
	FloodFillRecursive(grid, row, column + 1, value);
	FloodFillRecursive(grid, row + 1, column, value);
}

void FloodFillIterative(Grid& grid, const int& row, const int& column, const int& value)
{
	// Don't fill if the starting cell is invalid.
	if (!grid.isIndexValid(row, column) || grid.GetValueAt(row, column) == 1)
		return;

	std::list<std::pair<int, int>> stack;

	stack.push_back(std::pair<int, int>(row, column));

	while (!stack.empty())
	{
		// Pop the stack.
		std::pair<int, int> cell = stack.back();
		stack.pop_back();

		// Fill the cell.
		grid.SetValue(cell.first, cell.second, value);

		if (grid.isIndexValid(cell.first - 1, cell.second) && grid.GetValueAt(cell.first - 1, cell.second) == 0)
			stack.push_back(std::pair<int, int>(cell.first - 1, cell.second));
		if (grid.isIndexValid(cell.first, cell.second - 1) && grid.GetValueAt(cell.first, cell.second - 1) == 0)
			stack.push_back(std::pair<int, int>(cell.first, cell.second - 1));
		if (grid.isIndexValid(cell.first, cell.second + 1) && grid.GetValueAt(cell.first, cell.second + 1) == 0)
			stack.push_back(std::pair<int, int>(cell.first, cell.second + 1));
		if (grid.isIndexValid(cell.first + 1, cell.second) && grid.GetValueAt(cell.first + 1, cell.second) == 0)
			stack.push_back(std::pair<int, int>(cell.first + 1, cell.second));
	}
}

Grid GenerateGrid(const int& n)
{
	std::vector<std::vector<int>> values(n);

	for (int row = 0; row < values.size(); row++)
	{
		values[row].resize(n);
	}

	return Grid(values);
}

int GetRandomInteger(int minInclusive, int maxInclusive)
{
	static std::random_device randomDevice;
	static std::default_random_engine engine{randomDevice()};
	std::uniform_int_distribution<int> distribution{ minInclusive, maxInclusive };
	return distribution(engine);
}

void RandomlySetValue(Grid& grid, const int& newValue, int elementsToReplace)
{
	if (elementsToReplace < 1)
		return;

	// std::srand(std::time(nullptr));

	int replacedElements = 0;

	while (replacedElements < elementsToReplace)
	{
		int randomRow = GetRandomInteger(0, grid.GetSizeX() - 1);
		int randomColumn = GetRandomInteger(0, grid.GetSizeY() - 1);

		if (grid.GetValueAt(randomRow, randomColumn) != newValue)
		{
			grid.SetValue(randomRow, randomColumn, newValue);
			replacedElements++;
		}
	}
}

std::pair<int, int> GetRandomStartingCell(const Grid& grid, const int& valueToIgnore)
{
	std::pair<int, int> cell;
	cell.first = -1;
	cell.second = -1;

	if (grid.GetSizeX() == 0 || grid.GetSizeY() == 0)
	{
		cell.first = -1;
		cell.second = -1;
		return cell;
	}

	do
	{
		cell.first = GetRandomInteger(0, grid.GetSizeX() - 1);
		cell.second = GetRandomInteger(0, grid.GetSizeY() - 1);
	} while (!grid.isIndexValid(cell.first, cell.second) || grid.GetValueAt(cell.first, cell.second) == valueToIgnore);

	return cell;
}

bool GenerateDataFile(const std::string& dataFileName, const int& minN, const int& maxN)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);
	
	if (!dataFile)
		return false;

	dataFile << "#n\tRecursive(ns)\tIterative(ns)" << std::endl;

	// Get a seed for generating random numbers.
	std::srand(std::time(nullptr));

	for (int n = minN; n <= maxN; n++)
	{
		// Generate a grid. Replace 30% of the grid with 1.
		Grid grid0 = GenerateGrid(n);
		RandomlySetValue(grid0, 1, grid0.GetSizeX() * grid0.GetSizeY() * 0.3f);

		// Get the starting cell where flood-filling begins.
		std::pair<int, int> startingCell = GetRandomStartingCell(grid0, 1);

		// Flood-fill the grid recursively.
		Grid grid1(grid0);
		auto startTime1 = std::chrono::high_resolution_clock::now();
		FloodFillRecursive(grid1, startingCell.first, startingCell.second, 5);
		auto stopTime1 = std::chrono::high_resolution_clock::now();
		auto timeInterval1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime1 - startTime1).count();

		// Flood-fill the grid iteratively.
		Grid grid2(grid0);
		auto startTime2 = std::chrono::high_resolution_clock::now();
		FloodFillIterative(grid2, startingCell.first, startingCell.second, 5);
		auto stopTime2 = std::chrono::high_resolution_clock::now();
		auto timeInterval2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime2 - startTime2).count();

		// Print out a row.
		dataFile << n << "\t" << timeInterval1 << "\t" << timeInterval2 << "\n";

		std::cout << "n=" << n << " has been printed out.\tRecursive floodfill: " << timeInterval1 << " ns.\tIterative floodfill: " << timeInterval2 << " ns." << std::endl;
	}

	// Close the data file.
	dataFile.close();

	return true;
}

bool GenerateScriptFile(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1920,1080"							<< std::endl
		<< "set output '" << outputFileName << "'"						<< std::endl
																		<< std::endl
		<< "set title 'Recursive Flood Fill vs Imperative Flood Fill'"	<< std::endl
		<< "set xlabel 'N'"												<< std::endl
		<< "set ylabel 'Time (ns)'"										<< std::endl
		<< "set xzeroaxis"												<< std::endl
		<< "set key inside top left"									<< std::endl
																		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Recursive Flood Fill' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Imperative Flood Fill' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

void TestFloodFillOutput()
{
	// Test generating a grid.
	Grid grid0 = GenerateGrid(GetRandomInteger(10, 50));
	RandomlySetValue(grid0, 1, grid0.GetSizeX() * grid0.GetSizeY() * 0.3f);
	PrintGrid(grid0);

	// Get the starting cell.
	std::pair<int, int> startingCell = GetRandomStartingCell(grid0, 1);
	std::cout << "Starting position: (" << startingCell.first << ", " << startingCell.second << ")" << std::endl;

	//Test flood-filling the grid recursively.
	PrintGrid(grid0, startingCell);

	Grid grid1(grid0);

	auto startTime1 = std::chrono::high_resolution_clock::now();
	FloodFillRecursive(grid1, startingCell.first, startingCell.second, 5);
	auto stopTime1 = std::chrono::high_resolution_clock::now();

	auto timeInterval1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime1 - startTime1).count();

	PrintGrid(grid1, startingCell);
	std::cout << "Execution time for recursive flood fill: " << timeInterval1 << " ns" << std::endl;

	// Test flood-filling the grid iteratively.
	PrintGrid(grid0, startingCell);

	Grid grid2(grid0);

	auto startTime2 = std::chrono::high_resolution_clock::now();
	FloodFillIterative(grid2, startingCell.first, startingCell.second, 5);
	auto stopTime2 = std::chrono::high_resolution_clock::now();

	auto timeInterval2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime2 - startTime2).count();

	PrintGrid(grid2, startingCell);
	std::cout << "Execution time for iterative flood fill: " << timeInterval2 << " ns" << std::endl;
}
