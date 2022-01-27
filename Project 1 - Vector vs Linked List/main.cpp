#include <iostream>
#include "Vector.h"

void PrintVector(Vector<int>& vector)
{
	// Print the elements.
	std::cout << "Elements: ";
	for (int i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i] << ' ';
	}
	std::cout << std::endl;

	// Print the size.
	std::cout << "Size: " << vector.Size() << std::endl;

	// Print the capacity.
	std::cout << "Capacity: " << vector.GetCapacity() << std::endl;
}

int main()
{
	// Test constructor and destructor.
	/*
	{
		{
			Vector<int> numbers;
			numbers.Reserve(20000000);
			system("pause");
		}
		system("pause");
	}
	*/

	// Test pushing elements to the back.
	{
		{
			Vector<int> numbers1;
			numbers1.PushBack(7);
			numbers1.PushBack(5);
			numbers1.PushBack(3);
			numbers1.PushBack(4);
			numbers1.PushBack(1);

			PrintVector(numbers1);
		}

		{
			Vector<int> numbers2;
			numbers2.Reserve(3);

			numbers2.PushBack(7);
			numbers2.PushBack(5);
			numbers2.PushBack(3);
			numbers2.PushBack(4);
			numbers2.PushBack(1);

			PrintVector(numbers2);
		}

		{
			Vector<int> numbers3;
			numbers3.Reserve(5);

			numbers3.PushBack(7);
			numbers3.PushBack(5);
			numbers3.PushBack(3);
			numbers3.PushBack(4);
			numbers3.PushBack(1);

			PrintVector(numbers3);
		}
	}

	/*
	{
		Vector<int> numbers;

		numbers.Resize(10);

		for (int i = 0; i < numbers.Size(); i++)
		{
			std::cout << numbers[i] << ' ';
		}
		std::cout << std::endl;

		std::cout << "Size: " << numbers.Size() << std::endl;
		std::cout << "Capacity: " << numbers.GetCapacity() << std::endl;
	}
	*/

	/*
	{
		Vector<int> numbers;
		numbers.Resize(10);
		numbers.Insert(2, 4);

		for (int i = 0; i < numbers.Size(); i++)
		{
			std::cout << numbers[i] << ' ';
		}
		std::cout << std::endl;

		std::cout << "Size: " << numbers.Size() << std::endl;
		std::cout << "Capacity: " << numbers.GetCapacity() << std::endl;
	}
	*/
}