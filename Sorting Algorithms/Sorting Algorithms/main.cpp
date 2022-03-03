#include <iostream>
#include <fstream>
#include <chrono>
#include "Vector.h"
#include "Random.h"

template<class T>
void PrintVector(Vector<T>& vector)
{
	std::cout << "Vector's elements: ";
	if (vector.Size() == 0)
	{
		std::cout << "none";
	}
	else
	{
		for (int i = 0; i < vector.Size(); i++)
		{
			std::cout << vector[i] << ' ';
		}
	}
	std::cout << std::endl;
}

template<class T>
void Swap(T& val1, T& val2)
{
	T temp = val1;
	val1 = val2;
	val2 = temp;
}

template<class T>
void ReverseOrder(Vector<T>& vector)
{
	for (int i = 0; i < vector.Size() / 2; i++)
	{
		Swap(vector[i], vector[vector.Size() - i - 1]);
	}
}

template<class T>
void BubbleSort(Vector<T>& vector)
{
	for (int i = 0; i < vector.Size(); i++)
	{
		for (int j = 0; j < vector.Size() - i - 1; j++)
		{
			if (vector[j + 1] < vector[j])
			{
				Swap(vector[j], vector[j + 1]);
			}
		}
	}
}

template <class T>
void InsertionSort(Vector<T>& vector)
{
	for (int i = 0; i < vector.Size(); i++)
	{
		for (int j = i; j > 0 && vector[j] < vector[j - 1]; j--)
		{
			Swap(vector[j], vector[j - 1]);
		}
	}
}

template <class T>
void SelectionSort(Vector<T>& vector)
{
	for (int i = 0; i < vector.Size() - 1; i++)
	{
		for (int j = i + 1; j < vector.Size(); j++)
		{
			if (vector[j] < vector[i])
			{
				Swap(vector[j], vector[i]);
			}
		}
	}
}

void TestBubbleSort(Random& rand)
{
	// Open the file.
	std::ofstream dataFile("data_bubble_sort.txt", std::ios::trunc);
	if (!dataFile)
	{
		std::cout << "Cannot open the file data_bubble_sort.txt." << std::endl;
		return;
	}

	dataFile << "# BubbleSort() randomized input." << std::endl;
	dataFile << "#\tN\tBestCase\tWorstCase\tAverageCase" << std::endl;

	for (int n = 1; n <= 1000; n += 10)
	{
		long long bestCaseTime;
		long long worstCaseTime;
		long long averageCaseTime;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

		// Average case (elements are in random order).
		Vector<int> vector;
		vector.Resize(n);

		for (int i = 0; i < vector.Size(); i++)
		{
			vector[i] = rand.Integer(0, n);
		}

		startTime = std::chrono::high_resolution_clock::now();
		BubbleSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		averageCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Best case (elements are in ascending order).
		startTime = std::chrono::high_resolution_clock::now();
		BubbleSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		bestCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Worst case (elements are in descending order).
		ReverseOrder(vector);

		startTime = std::chrono::high_resolution_clock::now();
		BubbleSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		worstCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
		
		// Write the times to the file.
		dataFile << n << '\t' << bestCaseTime << '\t' << worstCaseTime << '\t' << averageCaseTime << std::endl;
	}

	// Close the file.
	dataFile.close();
}

void TestInsertionSort(Random& rand)
{
	// Open the file.
	std::ofstream dataFile("data_insertion_sort.txt", std::ios::trunc);
	if (!dataFile)
	{
		std::cout << "Cannot open the file data_insertion_sort.txt." << std::endl;
		return;
	}

	dataFile << "# InsertionSort() randomized input." << std::endl;
	dataFile << "#\tN\tBestCase\tWorstCase\tAverageCase" << std::endl;

	for (int n = 1; n <= 1000; n += 10)
	{
		long long bestCaseTime;
		long long worstCaseTime;
		long long averageCaseTime;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

		// Average case (elements are in random order).
		Vector<int> vector;
		vector.Resize(n);

		for (int i = 0; i < vector.Size(); i++)
		{
			vector[i] = rand.Integer(0, n);
		}

		startTime = std::chrono::high_resolution_clock::now();
		InsertionSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		averageCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Best case (elements are in ascending order).
		startTime = std::chrono::high_resolution_clock::now();
		InsertionSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		bestCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Worst case (elements are in descending order).
		ReverseOrder(vector);

		startTime = std::chrono::high_resolution_clock::now();
		InsertionSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		worstCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Write the times to the file.
		dataFile << n << '\t' << bestCaseTime << '\t' << worstCaseTime << '\t' << averageCaseTime << std::endl;
	}

	// Close the file.
	dataFile.close();
}

void TestSelectionSort(Random& rand)
{
	// Open the file.
	std::ofstream dataFile("data_selection_sort.txt", std::ios::trunc);
	if (!dataFile)
	{
		std::cout << "Cannot open the file data_selection_sort.txt." << std::endl;
		return;
	}

	dataFile << "# SelectionSort() randomized input." << std::endl;
	dataFile << "#\tN\tBestCase\tWorstCase\tAverageCase" << std::endl;

	for (int n = 1; n <= 1000; n += 10)
	{
		long long bestCaseTime;
		long long worstCaseTime;
		long long averageCaseTime;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

		// Average case (elements are in random order).
		Vector<int> vector;
		vector.Resize(n);

		for (int i = 0; i < vector.Size(); i++)
		{
			vector[i] = rand.Integer(0, n);
		}

		startTime = std::chrono::high_resolution_clock::now();
		SelectionSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		averageCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Best case (elements are in ascending order).
		startTime = std::chrono::high_resolution_clock::now();
		SelectionSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		bestCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Worst case (elements are in descending order).
		ReverseOrder(vector);

		startTime = std::chrono::high_resolution_clock::now();
		SelectionSort(vector);
		endTime = std::chrono::high_resolution_clock::now();

		worstCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Write the times to the file.
		dataFile << n << '\t' << bestCaseTime << '\t' << worstCaseTime << '\t' << averageCaseTime << std::endl;
	}

	// Close the file.
	dataFile.close();
}

int main()
{	
	Random rand;

	/*
	// Test reversing a vector.
	{
		Vector<int> numbers;
		numbers.Reserve(10);

		for (int i = 0; i < 10; i++)
		{
			numbers.PushBack(rand.Integer(0, 100));
		}

		PrintVector(numbers);

		ReverseOrder(numbers);

		PrintVector(numbers);
	}

	// Test bubble sort.
	{
		Vector<int> numbers;
		numbers.Reserve(10);

		for (int i = 0; i < 20; i++)
		{
			numbers.PushBack(rand.Integer(0, 100));
		}

		PrintVector(numbers);

		BubbleSort(numbers);

		PrintVector(numbers);
	}

	// Test insertion sort.
	{
		Vector<int> numbers;
		numbers.Reserve(10);

		for (int i = 0; i < 20; i++)
		{
			numbers.PushBack(rand.Integer(0, 100));
		}

		PrintVector(numbers);

		InsertionSort(numbers);

		PrintVector(numbers);
	}

	// Test selection sort.
	{
		Vector<int> numbers;
		numbers.Reserve(10);

		for (int i = 0; i < 20; i++)
		{
			numbers.PushBack(rand.Integer(0, 100));
		}

		PrintVector(numbers);

		SelectionSort(numbers);

		PrintVector(numbers);
	}
	*/

	TestBubbleSort(rand);
	TestInsertionSort(rand);
	TestSelectionSort(rand);

	system("gnuplot.exe script_best_case.txt");
	system("gnuplot.exe script_worst_case.txt");
	system("gnuplot.exe script_average_case.txt");
}