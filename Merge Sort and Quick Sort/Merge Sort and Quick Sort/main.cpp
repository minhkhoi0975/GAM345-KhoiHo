// Name(s): Khoi Ho, Matt Mills, Ethem Ficici

#include <iostream>
#include <fstream>
#include <chrono>
#include "Vector.h"
#include "Random.h"

template <class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<class T>
void PrintVector(Vector<T>& vector)
{
	const int size = vector.Size();

	for (int i = 0; i < size; i++)
	{
		std::cout << vector[i] << ' ';
	}
	std::cout << std::endl;
}

// -------------------------------
// Selection Sort
// -------------------------------

template <class T>
void SelectionSort(Vector<T>& vector)
{
	for (int i = 0; i < vector.Size() - 1; i++)
	{
		int minIndex = i;

		for (int j = i + 1; j < vector.Size(); j++)
		{
			if (vector[j] < vector[minIndex])
			{
				minIndex = j;
			}
		}

		Swap(vector[i], vector[minIndex]);
	}
}

// -------------------------------
// Merge Sort
// -------------------------------

template <class T>
void MergeSortRecursive(Vector<T>& vector)
{
	MergeSortRecursive(vector, 0, vector.Size() - 1);
}

template <class T>
void MergeSortRecursive(Vector<T>& vector, const int& start, const int& end)
{
	// Don't sort if the size of the subvector is 1 or lower.
	if (end - start <= 0)
		return;

	int mid = start + (end - start) / 2;

	// Sort the left half of the subvector.
	MergeSortRecursive(vector, start, mid);

	// Sort the right half of the subvector.
	MergeSortRecursive(vector, mid + 1, end);

	// Merge the two halves together.
	Merge(vector, start, mid, end);
}

template <class T>
void Merge(Vector<T>& numbers, const int& start, const int& mid, const int& end)
{
	// Create a temporary vector.
	int tempVectorSize = end - start + 1;
	Vector<T> tempVector;
	tempVector.Resize(tempVectorSize);

	// Put the elements into the temporary vector.
	int i = 0;
	int leftIndex = start;
	int rightIndex = mid + 1;
	while (leftIndex <= mid && rightIndex <= end)
	{
		if (numbers[leftIndex] <= numbers[rightIndex])
		{
			tempVector[i] = numbers[leftIndex];
			++leftIndex;
		}
		else
		{
			tempVector[i] = numbers[rightIndex];
			++rightIndex;
		}

		++i;
	}

	// Deal with the cases when there are still some elements left in the left subvector.
	while (leftIndex <= mid)
	{
		tempVector[i] = numbers[leftIndex];
		++leftIndex;
		++i;
	}

	// Deal with the cases when there are still some elements left in the right subvector.
	while (rightIndex <= end)
	{
		tempVector[i] = numbers[rightIndex];
		++rightIndex;
		++i;
	}

	// Copy the elements of the temporary array back to the original vector.
	for (int i = 0; i < tempVectorSize; ++i)
	{
		numbers[start + i] = tempVector[i];
	}
}

// -------------------------------
// Quick Sort
// -------------------------------

template <class T>
void QuickSortRecursive(Vector<T>& vector)
{
	QuickSortRecursive(vector, 0, vector.Size() - 1);
}

template <class T>
void QuickSortRecursive(Vector<T>& vector, const int& start, const int& end)
{
	// Don't sort if the size of the subvector is 1 or lower.
	if (end - start <= 0)
		return;

	// Partition the vector.
	int pivot = Partition(vector, start, end);

	// Quick sort the subvector on the left of the pivot.
	QuickSortRecursive(vector, start, pivot - 1);

	// Quick sort the subvector on the right of the pivot.
	QuickSortRecursive(vector, pivot + 1, end);
}

template <class T>
int Partition(Vector<T>& vector, const int& start, const int& end)
{
	// The pivot is the leftmost element of the vector.
	T pivot = vector[start];

	// Move the elements.
	int leftIndex = start;
	int rightIndex = end;
	bool currentIndex = true;  // true = right index, false = left index

	while (leftIndex < rightIndex)
	{
		if (currentIndex)
		{
			if (vector[rightIndex] < pivot)
			{
				vector[leftIndex] = vector[rightIndex];
				++leftIndex;
				currentIndex = false;
			}
			else
			{
				--rightIndex;
			}
		}
		else
		{
			if (vector[leftIndex] > pivot)
			{
				vector[rightIndex] = vector[leftIndex];
				--rightIndex;
				currentIndex = true;
			}
			else
			{
				++leftIndex;
			}
		}
	}

	// Move the pivot to the empty slot.
	vector[leftIndex] = pivot;

	// Return the pivot.
	return leftIndex;
}

// -------------------------------
// Sorting time measurement
// -------------------------------

typedef void (*SortingFunction)(Vector<int>& vector);

template<class T>
long long MeasureSortingTime(const Vector<T>& vector, SortingFunction sortingFunction)
{
	// Create a copy of the vector.
	Vector<T> copy(vector);

	// Measure the sorting time.
	auto startTime = std::chrono::high_resolution_clock::now();
	sortingFunction(copy);
	auto endTime = std::chrono::high_resolution_clock::now();

	// Return the sorting time in nanoseconds.
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}

bool GenerateDataAverageCase(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return false;

	dataFile << "#n\tQuickSort(ns)\tMergeSortList(ns)\tSelectionSort(ns)" << std::endl;

	for (int n = minN; n <= maxN; n++)
	{
		// Resize the vector.
		Vector<int> numbers;
		numbers.Resize(n);
		 
		std::cout << "n = " << n << std::endl;
		
		// Measure the average time of each sorting algorithm.
		long long quickSortAverageTime = 0;
		long long mergeSortAverageTime = 0;
		long long selectionSortAverageTime = 0;

		for (int i = 0; i < 100; i++)
		{
			// Generate random elements for the vector.
			for (int i = 0; i < n; i++)
			{
				numbers[i] = random.Integer(1, n);
			}

			// Measure and add the time to the total time.
			quickSortAverageTime += MeasureSortingTime(numbers, QuickSortRecursive);
			mergeSortAverageTime += MeasureSortingTime(numbers, MergeSortRecursive);
			selectionSortAverageTime += MeasureSortingTime(numbers, SelectionSort);
		}

		// Calculate the average time.
		quickSortAverageTime /= 100;
		mergeSortAverageTime /= 100;
		selectionSortAverageTime /= 100;

		// Write the average times to the file.
		dataFile << n << '\t' << quickSortAverageTime << '\t' << mergeSortAverageTime << '\t' << selectionSortAverageTime << '\n';
	}

	dataFile.close();

	return true;
}

// outPutFile1 is for Quick Sort vs Merge Sort, and outputFile2 is for QuickSort vs Selection Sort.
bool GenerateScriptAverageCase(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName1, const std::string& outputFileName2)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the script.
	scriptFile
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName1 << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of Quick Sort vs Merge Sort'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Quick Sort' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Merge Sort' lw 1 with lines" << std::endl

		<< std::endl

		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName2 << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of Quick Sort vs Selection Sort'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Quick Sort' lw 1 with lines, \"" << dataFileName << "\" using 1:4 title 'Selection Sort' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}


int main()
{
	
	// Create a vector of random numbers.
	Random random;

	/*
	const int MAX_VECTOR_SIZE = 1000;
	const int MIN_INT_VAL = 1;
	const int MAX_INT_VAL = 100;

	for (int arrSize = 2; arrSize <= MAX_VECTOR_SIZE; ++arrSize)
	{
		Vector<int> numbers;
		numbers.Resize(arrSize);
		for (int i = 0; i < arrSize; i++)
		{
			numbers[i] = random.Integer(1, arrSize);
		}

		// PrintVector(numbers);

		// Merge sort.
		//MergeSortRecursive(numbers);

		// Quick sort.
		// QuickSortRecursive(numbers);

		// Test sorting time measurement.
		auto quickSortTime = MeasureSortingTime(numbers, QuickSortRecursive);
		auto mergeSortTime = MeasureSortingTime(numbers, MergeSortRecursive);
		auto selectionSortTime = MeasureSortingTime(numbers, SelectionSort);

		std::cout << "Size = " << arrSize << "\tQuick Sort: " << quickSortTime << "ns" << "\tMerge Sort: " << mergeSortTime << "ns" << "\tSelection Sort: " << selectionSortTime << "ns" << std::endl;
	}
	*/

	GenerateDataAverageCase("average_case_data.txt", 1, 200, random);
	GenerateScriptAverageCase("average_case_script.txt", "average_case_data.txt", "average_case_output_quicksort_vs_mergesort.png", "average_case_output_quicksort_vs_selectionsort.png");
	system("gnuplot average_case_script.txt");

	// PrintVector(numbers);
}