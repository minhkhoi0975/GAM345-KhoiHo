// Name(s): Khoi Ho, Matt Mills, Ethem Ficici

#include <iostream>
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

int main()
{
	// Create an array of random numbers.
	Random random;
	const int ARR_SIZE = 20;
	const int MIN_INT_VAL = 1;
	const int MAX_INT_VAL = 100;

	int numbers[ARR_SIZE];
	for (int i = 0; i < ARR_SIZE; ++i)
	{
		numbers[i] = random.Integer(MIN_INT_VAL, MAX_INT_VAL);
	}

	PrintArray(numbers, ARR_SIZE);

	// Sort the array.
	MergeSortRecursive(numbers, 0, ARR_SIZE - 1);

	PrintArray(numbers, ARR_SIZE);
}