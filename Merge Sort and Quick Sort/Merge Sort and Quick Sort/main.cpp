// Name(s): Khoi Ho, Matt Mills, Ethem Ficici

#include <iostream>
#include "Vector.h"
#include "Random.h"

void Merge(int* numbers, int start, int mid, int end)
{
	// Create a temporary array.
	int tempArrSize = end - start + 1;
	int* tempArr = new int[tempArrSize];

	// Put the elements into the temporary array.
	int i = 0;
	int leftIndex = start;
	int rightIndex = mid + 1;
	while (leftIndex <= mid && rightIndex <= end)
	{
		if (numbers[leftIndex] <= numbers[rightIndex])
		{
			tempArr[i] = numbers[leftIndex];
			++leftIndex;
		}
		else
		{
			tempArr[i] = numbers[rightIndex];
			++rightIndex;
		}

		++i;
	}

	// Deal with the cases when there are still some elements left in the left subarray.
	while (leftIndex <= mid)
	{
		tempArr[i] = numbers[leftIndex];
		++leftIndex;
		++i;
	}

	// Deal with the cases when there are still some elements left in the right subarray.
	while (rightIndex <= end)
	{
		tempArr[i] = numbers[rightIndex];
		++rightIndex;
		++i;
	}
	
	// Copy the elements of the temporary array back to the original array.
	for (int i = 0; i < tempArrSize; ++i)
	{
		numbers[start + i] = tempArr[i];
	}

	// Delete the temporary array to avoid memory leak.
	delete[] tempArr;
}

void MergeSortRecursive(int* numbers, int start, int end)
{
	// Don't sort if the size of the subarray is 1 or lower.
	if (end - start <= 0)
		return;

	int mid = start + (end - start) / 2;

	// Sort the left half of the subarray.
	MergeSortRecursive(numbers, start, mid);

	// Sort the right half of the subarray.
	MergeSortRecursive(numbers, mid + 1, end);

	// Merge the two halves together.
	Merge(numbers, start, mid, end);
}

void PrintArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}

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

int main()
{
	// Create a vector of random numbers.
	Random random;
	const int VECTOR_SIZE = 10;
	const int MIN_INT_VAL = 1;
	const int MAX_INT_VAL = 100;

	Vector<int> numbers;
	numbers.Resize(VECTOR_SIZE);
	for (int i = 0; i < VECTOR_SIZE; i++)
	{
		numbers[i] = random.Integer(MIN_INT_VAL, MAX_INT_VAL);
	}

	PrintVector(numbers);

	// Merge sort.
	MergeSortRecursive(numbers);

	PrintVector(numbers);
}