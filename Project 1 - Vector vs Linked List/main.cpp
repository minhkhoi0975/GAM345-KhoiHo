#include <iostream>
#include "Vector.h"

int main()
{
	Vector<int> numbers;
	numbers.Reserve(10);

	numbers.PushBack(7);
	numbers.PushBack(4);
	numbers.PushBack(1);
	numbers.PushBack(5);
	numbers.PushBack(3);
	numbers.PushBack(6);

	/*
	std::cout << "Size: " << numbers.Size() << std::endl;
	std::cout << "Capacity: " << numbers.GetCapacity() << std::endl;

	for (int i = 0; i < numbers.Size(); i++)
	{
		std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;
	*/

	/*
	numbers.EraseAt(2);

	std::cout << "Size: " << numbers.Size() << std::endl;
	std::cout << "Capacity: " << numbers.GetCapacity() << std::endl;

	for (int i = 0; i < numbers.Size(); i++)
	{
		std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;
	*/

	/*
	numbers.Erase(5);

	std::cout << "Size: " << numbers.Size() << std::endl;
	std::cout << "Capacity: " << numbers.GetCapacity() << std::endl;

	for (int i = 0; i < numbers.Size(); i++)
	{
		std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;
	*/

	for (int i = 0; i < numbers.Size(); i++)
	{
		std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;

	{
		int valueToFind = 5;
		std::cout << "First element with value " << 5 << " is at index " << numbers.Find(valueToFind) << std::endl;
	}
	{
		int valueToFind = 0;
		std::cout << "First element with value " << 5 << " is at index " << numbers.Find(valueToFind) << std::endl;
	}
	{
		int valueToFind = 5;
		std::cout << "The vector " << (numbers.Contains(valueToFind) ? "contains " : "does not contain ") << valueToFind << std::endl;
	}
	{
		int valueToFind = 0;
		std::cout << "The vector " << (numbers.Contains(valueToFind) ? "contains " : "does not contain ") << valueToFind << std::endl;
	}
}