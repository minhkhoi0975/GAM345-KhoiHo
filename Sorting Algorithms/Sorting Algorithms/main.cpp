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

void TestBubbleSort()
{
	for (int n = 1; n <= 1000; n += 10)
	{
		// Best case.
		Vector<int> vector0;
		vector0.Reserve(n);

		for (int i = 0; i < n; i++)
		{
			vector0[i] = i;
		}
	}
}

int main()
{	
	Random rand;

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
}