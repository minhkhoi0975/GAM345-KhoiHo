#include <iostream>
#include "Vector.h"
#include "LinkedList.h"

void PrintVector(Vector<int>& vector)
{
	std::cout << std::endl;

	// Print the elements.
	std::cout << "Elements: ";
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

	// Print the size.
	std::cout << "Size: " << vector.Size() << std::endl;

	// Print the capacity.
	std::cout << "Capacity: " << vector.GetCapacity() << std::endl;

	std::cout << std::endl;
}

void TestVector()
{
	Vector<int> numbers;

	// Reserve 10 elements.
	numbers.Reserve(10);
	PrintVector(numbers);

	// Push back 5 elements.
	numbers.PushBack(7);
	numbers.PushBack(5);
	numbers.PushBack(3);
	numbers.PushBack(4);
	numbers.PushBack(1);;
	PrintVector(numbers);

	// Push front 2 elements.
	numbers.PushFront(2);
	numbers.PushFront(6);
	PrintVector(numbers);

	// Add an element at the beginning of the vector.
	numbers.Insert(14, 0);
	PrintVector(numbers);

	// Add an element in the middle of the vector.
	numbers.Insert(19, 4);
	PrintVector(numbers);

	// Add an element at the end of the vector.
	numbers.Insert(26, numbers.Size());
	PrintVector(numbers);

	// Add an element at the index outside the vector.
	numbers.Insert(70, 20);
	PrintVector(numbers);

	// Change the values of some elements.
	numbers[1] = 38;
	numbers.At(7) = 491;
	PrintVector(numbers);

	// Remove an element at the beginning of the vector.
	numbers.EraseAt(0);
	PrintVector(numbers);

	// Remove an element in the middle of the vector.
	numbers.EraseAt(3);
	PrintVector(numbers);

	// Remove an element at the end of the vector.
	numbers.EraseAt(numbers.Size() - 1);
	PrintVector(numbers);

	// Check if the vector contains values.
	int value1 = 1;
	std::cout << "The vector " << (numbers.Contains(value1) ? "contains " : "does not contain ") << value1 << std::endl;
	std::cout << "Value " << value1 << " is first found at element " << numbers.Find(value1) << std::endl;
	std::cout << std::endl;

	int value2 = 8;
	std::cout << "The vector " << (numbers.Contains(value2) ? "contains " : "does not contain ") << value2 << std::endl;
	std::cout << "Value " << value2 << " is first found at element " << numbers.Find(value2) << std::endl;
	std::cout << std::endl;

	// Clear the vector.
	numbers.Clear();
	PrintVector(numbers);
}

void PrintLinkedList(LinkedList<int>& linkedList)
{
	std::cout << std::endl;

	// Print the elements.
	std::cout << "Elements: ";

	if (linkedList.Size() == 0)
	{
		std::cout << "none";
	}
	else
	{
		for (int i = 0; i < linkedList.Size(); i++)
		{
			std::cout << linkedList[i] << ' ';
		}
	}
	std::cout << std::endl;

	// Print the size.
	std::cout << "Size: " << linkedList.Size() << std::endl;

	std::cout << std::endl;
}

void TestLinkedList()
{
	LinkedList<int> linkedList;
	PrintLinkedList(linkedList);

	linkedList.PushBack(5);
	linkedList.PushBack(7);
	linkedList.PushBack(1);
	linkedList.PushBack(3);
	linkedList.PushBack(9);
	PrintLinkedList(linkedList);

	linkedList.PushFront(3);
	linkedList.PushFront(4);
	PrintLinkedList(linkedList);

	linkedList.EraseAt(0);
	PrintLinkedList(linkedList);

	linkedList.EraseAt(3);
	PrintLinkedList(linkedList);

	linkedList.Erase(7);
	PrintLinkedList(linkedList);

	linkedList.Erase(9);
	PrintLinkedList(linkedList);

	linkedList.Erase(3);
	PrintLinkedList(linkedList);

	linkedList.PushBack(4);
	linkedList.PushBack(4);
	linkedList.PushBack(2);
	linkedList.PushBack(3);
	linkedList.PushBack(1);
	PrintLinkedList(linkedList);

	linkedList.Clear();
	PrintLinkedList(linkedList);
}

int main()
{	
	// TestVector();

	TestLinkedList();
}