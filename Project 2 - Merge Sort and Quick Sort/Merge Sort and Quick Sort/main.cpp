// Quick Sort
// Programmer: Khoi Ho

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

// Partition the vector. Return the position of the pivot after partition. (Source: https://www.youtube.com/watch?v=h_9kAXFKJwY).
template <class T>
int Partition(Vector<T>& vector, const int& start, const int& end)
{
	// The pivot is the leftmost element of the vector.
	T pivot = vector[start];

	int leftPointer = start;
	int rightPointer = end;
	bool isCurrentPointerRight = true;  // If true, the current iteration of the while loop moves the right pointer, otherwise it moves the left pointer.

	while (leftPointer < rightPointer)
	{
		if (isCurrentPointerRight)
		{
			if (vector[rightPointer] < pivot)
			{
				vector[leftPointer] = vector[rightPointer];
				++leftPointer;
				isCurrentPointerRight = false;
			}
			else
			{
				--rightPointer;
			}
		}
		else
		{
			if (vector[leftPointer] > pivot)
			{
				vector[rightPointer] = vector[leftPointer];
				--rightPointer;
				isCurrentPointerRight = true;
			}
			else
			{
				++leftPointer;
			}
		}
	}

	// Move the pivot to where the two pointers collide.
	vector[leftPointer] = pivot;

	// Return the pivot.
	return leftPointer;
}

// -------------------------------
// Testing
// -------------------------------

template <class T>
bool IsSorted(Vector<T>& vector)
{
	if (vector.Size() < 2)
		return true;

	for (int i = 0; i < vector.Size() - 1; i++)
	{
		if (vector[i] > vector[i + 1])
			return false;
	}

	return true;
}

// -------------------------------
// Sorting time measurement
// -------------------------------

// Generate the worst case for merge sort (source: https://stackoverflow.com/questions/24594112/when-will-the-worst-case-of-merge-sort-occur).
template<class T>
void GenerateWorstCaseMergeSort(Vector<T>& sortedVector)
{
	if (sortedVector.Size() <= 1)
		return;

	if (sortedVector.Size() == 2)
	{
		Swap(sortedVector[0], sortedVector[1]);
		return;
	}

	int mid = (sortedVector.Size() + 1) / 2;

	// Create left and right subvectors.
	Vector<T> leftHalf, rightHalf;
	leftHalf.Resize(mid);
	rightHalf.Resize(sortedVector.Size() - mid);

	int i, j;

	// Store elements with even indices in the left subvector.
	for (i = 0, j = 0; i < sortedVector.Size(); i += 2, ++j)
	{
		leftHalf[j] = sortedVector[i];
	}

	// Store elements with odd indices in the right subvector.
	for (i = 1, j = 0; i < sortedVector.Size(); i += 2, ++j)
	{
		rightHalf[j] = sortedVector[i];
	}

	// Recursively generate the worst case for each subvector.
	GenerateWorstCaseMergeSort(leftHalf);
	GenerateWorstCaseMergeSort(rightHalf);

	// Merge the subvectors together.
	Merge(sortedVector, leftHalf, rightHalf);
}

// Join leftHalf and rightHalf together.
template<class T>
void Merge(Vector<T>& mergedVector, Vector<T>& leftHalf, Vector<T>& rightHalf)
{
	int i, j;

	// Add elements from left subvector.
	for (i = 0; i < leftHalf.Size(); i++)
	{
		mergedVector[i] = leftHalf[i];
	}

	// Add elements from right subvector.
	for (j = 0; j < rightHalf.Size(); j++, i++)
	{
		mergedVector[i] = rightHalf[j];
	}
}

// Generate a data file for quick sort.
void TestQuickSort(const std::string& dataFileName, Random& rand)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return;

	dataFile << "# QuickSort() randomized input." << std::endl;
	dataFile << "#N\tWorstCase\tAverageCase" << std::endl;

	for (int n = 1; n <= 1000; n += 10)
	{
		long long worstCaseTime;
		long long averageCaseTime;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

		// Average case (elements are in random order).
		Vector<int> vector1;
		vector1.Resize(n);
		for (int i = 0; i < vector1.Size(); i++)
		{
			vector1[i] = rand.Integer(0, n);
		}

		startTime = std::chrono::high_resolution_clock::now();
		QuickSortRecursive(vector1);
		endTime = std::chrono::high_resolution_clock::now();

		averageCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Worst case (the vector is already sorted).
		Vector<int> vector2(vector1);
		QuickSortRecursive(vector2);

		startTime = std::chrono::high_resolution_clock::now();
		QuickSortRecursive(vector2);
		endTime = std::chrono::high_resolution_clock::now();

		worstCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Write the times to the file.
		dataFile << n << '\t' << worstCaseTime << '\t' << averageCaseTime << std::endl;
	}

	dataFile.close();
}

// Generate a data file for merge sort.
void TestMergeSort(const std::string& dataFileName, Random& rand)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return;

	dataFile << "# MergeSort() randomized input." << std::endl;
	dataFile << "#N\tWorstCase\tAverageCase" << std::endl;

	for (int n = 1; n <= 1000; n += 10)
	{
		long long worstCaseTime;
		long long averageCaseTime;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

		// Average case (elements are in random order).
		Vector<int> vector1;
		vector1.Resize(n);
		for (int i = 0; i < vector1.Size(); i++)
		{
			vector1[i] = rand.Integer(0, n);
		}

		startTime = std::chrono::high_resolution_clock::now();
		MergeSortRecursive(vector1);
		endTime = std::chrono::high_resolution_clock::now();

		averageCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Worst case (all the elements must be compared for each merging operation).
		Vector<int> vector2(vector1);
		QuickSortRecursive(vector2);
		GenerateWorstCaseMergeSort(vector2);

		startTime = std::chrono::high_resolution_clock::now();
		MergeSortRecursive(vector2);
		endTime = std::chrono::high_resolution_clock::now();

		worstCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Write the times to the file.
		dataFile << n << '\t' << worstCaseTime << '\t' << averageCaseTime << std::endl;
	}

	dataFile.close();
}

// Generate a data file for selection sort.
void TestSelectionSort(const std::string& dataFileName, Random& rand)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return;

	dataFile << "# SelectionSort() randomized input." << std::endl;
	dataFile << "#N\tWorstCase\tAverageCase" << std::endl;

	for (int n = 1; n <= 1000; n += 10)
	{
		long long worstCaseTime;
		long long averageCaseTime;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

		// Average case (elements are in random order).
		Vector<int> vector1;
		vector1.Resize(n);
		for (int i = 0; i < vector1.Size(); i++)
		{
			vector1[i] = rand.Integer(0, n);
		}

		startTime = std::chrono::high_resolution_clock::now();
		SelectionSort(vector1);
		endTime = std::chrono::high_resolution_clock::now();

		averageCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Worst case (the vector is sorted in reverse order).
		Vector<int> vector2(vector1);
		QuickSortRecursive(vector2);
		for (int i = 0; i < vector2.Size()/2; ++i)
		{
			Swap(vector2[i], vector2[vector2.Size() - 1 - i]);
		}

		startTime = std::chrono::high_resolution_clock::now();
		SelectionSort(vector2);
		endTime = std::chrono::high_resolution_clock::now();

		worstCaseTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		// Write the times to the file.
		dataFile << n << '\t' << worstCaseTime << '\t' << averageCaseTime << std::endl;
	}

	dataFile.close();
}

// Generate a script file for worst case. QS: Quick Sort, MS: Merge Sort, SS: Selection Sort.
void GenerateScriptWorstCase(const std::string& scriptFileName, const std::string& dataFileNameQS, const std::string& dataFileNameMS, const std::string& dataFileNameSS, 
	const std::string& outputFileNameAll, const std::string& outputFileNameQSMS, const std::string& outputFileNameQSSS, const std::string& outputFileNameQS, const std::string& outputFileNameMS, const std::string& outputFileNameSS)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return;

	// Print out the script.
	scriptFile
		<< "# Quick Sort vs Merge Sort vs Selection in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameAll << "'" << std::endl
		<< "set title 'Completion Time of Quick Sort vs Merge Sort vs Selection Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameQS << "\" using 1:2 title 'Quick Sort' lc 1 lw 5 with lines, \"" << dataFileNameMS << "\" using 1:2 title 'Merge Sort' lc 2 lw 5 with lines, \"" << dataFileNameSS << "\" using 1:2 title 'Selection Sort' lc 3 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Quick Sort vs Merge Sort in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameQSMS << "'" << std::endl
		<< "set title 'Completion Time of Quick Sort vs Merge Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameQS << "\" using 1:2 title 'Quick Sort' lc 1 lw 5 with lines, \"" << dataFileNameMS << "\" using 1:2 title 'Merge Sort' lc 2 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Quick Sort vs Selection Sort in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameQSSS << "'" << std::endl
		<< "set title 'Completion Time of Quick Sort vs Selection Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameQS << "\" using 1:2 title 'Quick Sort' lc 1 lw 5 with lines, \"" << dataFileNameSS << "\" using 1:2 title 'Selection Sort' lc 3 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Quick Sort in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameQS << "'" << std::endl
		<< "set title 'Completion Time of Quick Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameQS << "\" using 1:2 title 'Quick Sort' lc 1 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Merge Sort in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameMS << "'" << std::endl
		<< "set title 'Completion Time of Merge Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameMS << "\" using 1:2 title 'Merge Sort' lc 2 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Selection Sort in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameSS << "'" << std::endl
		<< "set title 'Completion Time of Selection Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameSS << "\" using 1:2 title 'Selection Sort' lc 3 lw 5 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return;
}

// Generate a script file for average case. QS: Quick Sort, MS: Merge Sort, SS: Selection Sort.
void GenerateScriptAverageCase(const std::string& scriptFileName, const std::string& dataFileNameQS, const std::string& dataFileNameMS, const std::string& dataFileNameSS, 
	const std::string& outputFileNameAll, const std::string& outputFileNameQSMS, const std::string& outputFileNameQSSS, const std::string& outputFileNameQS, const std::string& outputFileNameMS, const std::string& outputFileNameSS)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return;

	// Print out the script.
	scriptFile
		<< "# Quick Sort vs Merge Sort vs Selection in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameAll << "'" << std::endl
		<< "set title 'Completion Time of Quick Sort vs Merge Sort vs Selection Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameQS << "\" using 1:3 title 'Quick Sort' lc 1 lw 5 with lines, \"" << dataFileNameMS << "\" using 1:3 title 'Merge Sort' lc 2 lw 5 with lines, \"" << dataFileNameSS << "\" using 1:3 title 'Selection Sort' lc 3 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Quick Sort vs Merge Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameQSMS << "'" << std::endl
		<< "set title 'Completion Time of Quick Sort vs Merge Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameQS << "\" using 1:3 title 'Quick Sort' lc 1 lw 5 with lines, \"" << dataFileNameMS << "\" using 1:3 title 'Merge Sort' lc 2 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Quick Sort vs Selection Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameQSSS << "'" << std::endl
		<< "set title 'Completion Time of Quick Sort vs Selection Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameQS << "\" using 1:3 title 'Quick Sort' lc 1 lw 5 with lines, \"" << dataFileNameSS << "\" using 1:3 title 'Selection Sort' lc 3 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Quick Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameQS << "'" << std::endl
		<< "set title 'Completion Time of Quick Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameQS << "\" using 1:3 title 'Quick Sort' lc 1 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Merge Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameMS << "'" << std::endl
		<< "set title 'Completion Time of Merge Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameMS << "\" using 1:3 title 'Merge Sort' lc 2 lw 5 with lines" << std::endl

		<< std::endl

		<< "# Selection Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameSS << "'" << std::endl
		<< "set title 'Completion Time of Selection Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileNameSS << "\" using 1:3 title 'Selection Sort' lc 3 lw 5 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return;
}


int main()
{
	Random random;

	/*
	// Test the sorting algorithms
	{
		const int MAX_VECTOR_SIZE = 100;
		const int MIN_INT_VAL = 1;
		const int MAX_INT_VAL = 100;

		Vector<int> numbers;
		numbers.Resize(MAX_VECTOR_SIZE);
		for (int i = 0; i < MAX_VECTOR_SIZE; i++)
		{
			numbers[i] = random.Integer(MIN_INT_VAL, MAX_INT_VAL);
		}

		PrintVector(numbers);
		std::cout << (IsSorted(numbers) ? "The vector is sorted." : "The vector is not sorted.") << std::endl;

		// MergeSortRecursive(numbers);
		// QuickSortRecursive(numbers);
		// SelectionSort(numbers);

		PrintVector(numbers);
		std::cout << (IsSorted(numbers) ? "The vector is sorted." : "The vector is not sorted.") << std::endl;
	}
	*/

	/*
	// Test generating vectors for worst cases.
	{
		const int MAX_VECTOR_SIZE = 9;
		const int MIN_INT_VAL = 1;
		const int MAX_INT_VAL = 100;

		Vector<int> numbers;

		numbers.Resize(MAX_VECTOR_SIZE);
		for (int i = 0; i < MAX_VECTOR_SIZE; i++)
		{
			//numbers[i] = i;
			numbers[i] = random.Integer(MIN_INT_VAL, MAX_INT_VAL);
		}
		QuickSortRecursive(numbers);

		std::cout << "Sorted vector: ";
		PrintVector(numbers);

		Vector<int> mergeSortVector(numbers), quickSortVector(numbers), selectionSortVector(numbers);

		GenerateWorstCaseMergeSort(mergeSortVector);

		for (int i = 0; i < selectionSortVector.Size() / 2; ++i)
		{
			Swap(selectionSortVector[i], selectionSortVector[selectionSortVector.Size() - 1 - i]);
		}

		std::cout << "Quick sort's worst case: ";
		PrintVector(quickSortVector);

		std::cout << "Merge sort's worst case: ";
		PrintVector(mergeSortVector);

		std::cout << "Selection sort's worst case: ";
		PrintVector(selectionSortVector);
	}
	*/

	TestQuickSort("data_quicksort.txt", random);
	TestMergeSort("data_mergesort.txt", random);
	TestSelectionSort("data_selectionsort.txt", random);

	GenerateScriptWorstCase("script_worstcase.txt", "data_quicksort.txt", "data_mergesort.txt", "data_selectionsort.txt", 
		"image_worstcase_all.png", "image_worstcase_quicksort_vs_mergesort.png", "image_worstcase_quicksort_vs_selectionsort.png", "image_worstcase_quicksort.png", "image_worstcase_mergesort.png", "image_worstcase_selectionsort.png");

	GenerateScriptAverageCase("script_averagecase.txt", "data_quicksort.txt", "data_mergesort.txt", "data_selectionsort.txt", 
		"image_averagecase_all.png", "image_averagecase_quicksort_vs_mergesort.png", "image_averagecase_quicksort_vs_selectionsort.png", "image_averagecase_quicksort.png", "image_averagecase_mergesort.png", "image_averagecase_selectionsort.png");

	system("gnuplot script_worstcase.txt");
	system("gnuplot script_averagecase.txt");
}