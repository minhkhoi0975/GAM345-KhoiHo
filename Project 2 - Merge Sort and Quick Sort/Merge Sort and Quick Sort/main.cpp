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

/*
// Alternative partition algorithm (Source: https://www.youtube.com/watch?v=O5V5JTa3O20&ab_channel=ComputerScience).
template <class T>
int Partition(Vector<T>& vector, const int& start, const int& end)
{
	int leftPointer = start;
	int rightPointer = end;
	bool isCurrentPointerRight = true;  // If true, the current iteration of the while loop moves the right pointer, otherwise it moves the left pointer.

	while (leftPointer < rightPointer)
	{
		// Move the right pointer.
		if (isCurrentPointerRight)
		{
			if (vector[leftPointer] > vector[rightPointer])
			{
				Swap(vector[leftPointer], vector[rightPointer]);
				isCurrentPointerRight = false;
			}
			else
			{
				--rightPointer;
			}
		}

		// Move the left pointer.
		else
		{
			if (vector[leftPointer] > vector[rightPointer])
			{
				Swap(vector[leftPointer], vector[rightPointer]);
				isCurrentPointerRight = true;
			}
			else
			{
				++leftPointer;
			}
		}
	}

	// Return the pivot.
	return leftPointer;
}
*/

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

// Function pointer for sorting functions.
typedef void (*SortingFunction)(Vector<int>& vector);

long long MeasureSortingTime(const Vector<int>& vector, SortingFunction sortingFunction)
{
	// Create a copy of the vector.
	Vector<int> copy(vector);

	// Measure the sorting time.
	auto startTime = std::chrono::high_resolution_clock::now();
	sortingFunction(copy);
	auto endTime = std::chrono::high_resolution_clock::now();

	// Return the sorting time in nanoseconds.
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}

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

	Vector<T> leftHalf, rightHalf;
	leftHalf.Resize(mid);
	rightHalf.Resize(sortedVector.Size() - mid);

	int i, j;

	//Storing alternate elements in left subarray
	for (i = 0, j = 0; i < sortedVector.Size(); i += 2, ++j)
	{
		leftHalf[j] = sortedVector[i];
	}

	//Storing alternate elements in right subarray
	for (i = 1, j = 0; i < sortedVector.Size(); i += 2, ++j)
	{
		rightHalf[j] = sortedVector[i];
	}

	GenerateWorstCaseMergeSort(leftHalf);
	GenerateWorstCaseMergeSort(rightHalf);

	Merge(sortedVector, leftHalf, rightHalf);
}

// Join leftHalf and rightHalf together.
template<class T>
void Merge(Vector<T>& mergedVector, Vector<T>& leftHalf, Vector<T>& rightHalf)
{
	int i, j;

	// Add elements from left subarray.
	for (i = 0; i < leftHalf.Size(); i++)
	{
		mergedVector[i] = leftHalf[i];
	}

	// Add elements from right subarray.
	for (j = 0; j < rightHalf.Size(); j++, i++)
	{
		mergedVector[i] = rightHalf[j];
	}
}

// Generate the worst case for each sorting element:
// + Merge sort: For every merge operation, all the elements are compared (e.g. [4 0 6 2 5 1 7 3], [8 0 4 6 2 5 1 7 3]).
// + Quick sort: The elements are sorted.
// + Selection sort: The elements are sorted in reverse order.
template<class T>
void GenerateWorstCase(Vector<T>& sortedVector, Vector<T>& mergeSortVector, Vector<T>& quickSortVector, Vector<T>& selectionSortVector)
{
	// Get the size and half size of the vector.
	const int SIZE = sortedVector.Size();
	const int HALF_SIZE = SIZE / 2;

	// Generate the worst case for merge sort.
	mergeSortVector = sortedVector;
	GenerateWorstCaseMergeSort(mergeSortVector);

	// Generate the worst case for quick sort.
	quickSortVector = sortedVector;

	// Generate the worst case for selection sort.
	selectionSortVector = sortedVector;
	for (int i = 0; i < HALF_SIZE; ++i)
	{
		Swap(selectionSortVector[i], selectionSortVector[SIZE - 1 - i]);
	}
}

// Generate data for the WORST case of quick sort.
// Quick sort has the worst case when elements always move to one side of the pivot for every partition.
// Since the partition algorithm chooses the leftmost element as a pivot, quicksort is in worst case when the vector is already sorted.
bool GenerateDataWorstCase(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
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

			// Sort the vector.
			QuickSortRecursive(numbers);

			// Generate the worst case for each sorting algorithm.
			Vector<int> mergeSortVector, quickSortVector, selectionSortVector;
			GenerateWorstCase(numbers, mergeSortVector, quickSortVector, selectionSortVector);

			// Measure and add the time to the total time.
			quickSortAverageTime += MeasureSortingTime(quickSortVector, QuickSortRecursive);
			mergeSortAverageTime += MeasureSortingTime(mergeSortVector, MergeSortRecursive);
			selectionSortAverageTime += MeasureSortingTime(selectionSortVector, SelectionSort);
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

// outputFileNameAll is for Quick Sort vs Merge Sort vs Selection Sort
// outputFileNameQS is for Quick Sort only
// outputFileNameMS is for Merge Sort only
// outputFileNameSS is for Selection Sort only
bool GenerateScriptWorstCase(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileNameAll, const std::string& outputFileNameQS, const std::string& outputFileNameMS, const std::string& outputFileNameSS)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the script.
	scriptFile
		<< "# Quick Sort vs Merge Sort vs Selection in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameAll << "'" << std::endl
		<< "set title 'Average Completion Time of Quick Sort vs Merge Sort vs Selection Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Quick Sort' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Merge Sort' lw 1 with lines, \"" << dataFileName << "\" using 1:4 title 'Selection Sort' lw 1 with lines" << std::endl

		<< std::endl

		<< "# Quick Sort in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameQS << "'" << std::endl
		<< "set title 'Average Completion Time of Quick Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Quick Sort' lw 1 with lines" << std::endl

		<< std::endl

		<< "# Merge Sort in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameMS << "'" << std::endl
		<< "set title 'Average Completion Time of Merge Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileName << "\" using 1:3 title 'Merge Sort' lw 1 with lines" << std::endl

		<< std::endl

		<< "# Selection Sort in Worst Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameSS << "'" << std::endl
		<< "set title 'Average Completion Time of Selection Sort in Worst Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileName << "\" using 1:4 title 'Selection Sort' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

// Generate data for the AVERAGE case of quick sort.
// Quick sort has the average case when elements are divided into two unequal parts for every partition.
// Since the partition algorithm chooses the leftmost element as a pivot, quicksort is in worst case when the vector is already sorted.
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

// outputFileNameAll is for Quick Sort vs Merge Sort vs Selection Sort
// outputFileNameQS is for Quick Sort only
// outputFileNameMS is for Merge Sort only
// outputFileNameSS is for Selection Sort only
bool GenerateScriptAverageCase(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileNameAll, const std::string& outputFileNameQS, const std::string& outputFileNameMS, const std::string& outputFileNameSS)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the script.
	scriptFile
		<< "# Quick Sort vs Merge Sort vs Selection Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameAll << "'" << std::endl
		<< "set title 'Average Completion Time of Quick Sort vs Merge Sort vs Selection Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Quick Sort' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Merge Sort' lw 1 with lines, \"" << dataFileName << "\" using 1:4 title 'Selection Sort' lw 1 with lines" << std::endl

		<< std::endl

		<< "# Quick Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameQS << "'" << std::endl
		<< "set title 'Average Completion Time of Quick Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Quick Sort' lw 1 with lines" << std::endl

		<< std::endl

		<< "# Merge Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameMS << "'" << std::endl
		<< "set title 'Average Completion Time of Merge Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileName << "\" using 1:3 title 'Merge Sort' lw 1 with lines" << std::endl

		<< std::endl

		<< "# Selection Sort in Average Case" << std::endl
		<< "reset" << std::endl
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileNameSS << "'" << std::endl
		<< "set title 'Average Completion Time of Selection Sort in Average Case'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< "plot \"" << dataFileName << "\" using 1:4 title 'Selection Sort' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
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
		QuickSortRecursive(numbers);
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
			numbers[i] = i;
			//numbers[i] = random.Integer(MIN_INT_VAL, MAX_INT_VAL);
		}
		QuickSortRecursive(numbers);

		std::cout << "Sorted vector: ";
		PrintVector(numbers);

		Vector<int> mergeSortVector, quickSortVector, selectionSortVector;
		GenerateWorstCase(numbers, mergeSortVector, quickSortVector, selectionSortVector);

		std::cout << "Merge sort's worst case: ";
		PrintVector(mergeSortVector);

		std::cout << "Quick sort's worst case: ";
		PrintVector(quickSortVector);

		std::cout << "Selection sort's worst case: ";
		PrintVector(selectionSortVector);
	}
	*/

	// Worst case.
	GenerateDataWorstCase("worst_case_data.txt", 1, 200, random);
	GenerateScriptWorstCase("worst_case_script.txt", "worst_case_data.txt", "worst_case_output.png", "worst_case_output_quicksort_only.png", "worst_case_output_mergesort_only.png", "worst_case_output_selectionsort_only.png");
	system("gnuplot worst_case_script.txt");

	// Average case.
	GenerateDataAverageCase("average_case_data.txt", 1, 200, random);
	GenerateScriptAverageCase("average_case_script.txt", "average_case_data.txt", "average_case_output.png", "average_case_output_quicksort_only.png", "average_case_output_mergesort_only.png", "average_case_output_selectionsort_only.png");
	system("gnuplot average_case_script.txt");
}