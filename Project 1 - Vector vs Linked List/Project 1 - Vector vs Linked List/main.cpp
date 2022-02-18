#include <iostream>
#include "Vector.h"
#include "LinkedList.h"

template<class T>
void PrintVector(Vector<T>& vector)
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

void TestVectorRAII()
{
	// Create an object.
	Vector<int> vector1;
	vector1.PushBack(5);
	vector1.PushBack(6);
	vector1.PushBack(2);
	vector1.PushBack(7);
	vector1.PushBack(3);
	PrintVector(vector1);

	// Create a new object using copy constructor.
	{
		Vector<int> vector2(vector1);
		PrintVector(vector2);

		// Make changes in vector2 to check if vector1 is affected.
		vector2.PushBack(5);
		vector2.PushBack(4);
		vector2.PushBack(4);
		vector2.PushBack(1);

		PrintVector(vector2);
		PrintVector(vector1);
	}

	// Create a new object using assignment operator.
	{
		Vector<int> vector3 = vector1;
		PrintVector(vector3);

		// Make changes in vector3 to check if vector1 is affected.
		vector3.PushBack(2);
		vector3.PushBack(9);
		vector3.PushBack(9);
		vector3.PushBack(3);

		PrintVector(vector3);
		PrintVector(vector1);

		// Reassign vector3.
		vector3 = vector1;
		vector3.PushBack(2);
		vector3.PushBack(2);
		vector3.PushBack(4);
		vector3.PushBack(1);

		PrintVector(vector3);
		PrintVector(vector1);
	}
}

void TestVector()
{
	Vector<int> numbers;

	// Reserve 10 elements.
	numbers.Reserve(10);
	PrintVector(numbers);

	// Resize the vector to 5 elements.
	numbers.Resize(5);
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

	// Remove the first element that matches the value.
	numbers.Erase(7);
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

	// Resize the vector to 5 elements.
	numbers.Resize(5);
	PrintVector(numbers);

	// Clear the vector.
	numbers.Clear();
	PrintVector(numbers);
}

template<class T>
void PrintLinkedList(LinkedList<T>& linkedList)
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

	// Print the head and the tail.
	if (linkedList.Size() > 0)
	{
		std::cout << "Head: " << linkedList.GetHead() << std::endl;
		std::cout << "Tail: " << linkedList.GetTail() << std::endl;
	}
	else
	{
		std::cout << "Head: null" << std::endl;
		std::cout << "Tail: null" << std::endl;
	}

	std::cout << std::endl;
}

void TestLinkedListRAII()
{
	// Create an object.
	LinkedList<int> linkedList1;
	linkedList1.PushBack(5);
	linkedList1.PushBack(6);
	linkedList1.PushBack(2);
	linkedList1.PushBack(7);
	linkedList1.PushBack(3);
	PrintLinkedList(linkedList1);

	// Create a new object using copy constructor.
	{
		LinkedList<int> linkedList2(linkedList1);
		PrintLinkedList(linkedList2);

		// Make changes in vector2 to check if vector1 is affected.
		linkedList2.PushBack(5);
		linkedList2.PushBack(4);
		linkedList2.PushBack(4);
		linkedList2.PushBack(1);

		PrintLinkedList(linkedList2);
		PrintLinkedList(linkedList1);
	}

	// Create a new object using assignment operator.
	{
		LinkedList<int> linkedList3 = linkedList1;
		PrintLinkedList(linkedList3);

		// Make changes in vector3 to check if vector1 is affected.
		linkedList3.PushBack(2);
		linkedList3.PushBack(9);
		linkedList3.PushBack(9);
		linkedList3.PushBack(3);

		PrintLinkedList(linkedList3);
		PrintLinkedList(linkedList1);

		// Reassign vector3.
		linkedList3 = linkedList1;
		linkedList3.PushBack(2);
		linkedList3.PushBack(2);
		linkedList3.PushBack(4);
		linkedList3.PushBack(1);

		PrintLinkedList(linkedList3);
		PrintLinkedList(linkedList1);
	}
}

void TestLinkedList()
{
	LinkedList<int> linkedList;
	PrintLinkedList(linkedList);

	// Push back 5 elements.
	linkedList.PushBack(5);
	linkedList.PushBack(7);
	linkedList.PushBack(1);
	linkedList.PushBack(3);
	linkedList.PushBack(9);
	PrintLinkedList(linkedList);

	// Push front 2 elements.
	linkedList.PushFront(3);
	linkedList.PushFront(4);
	PrintLinkedList(linkedList);

	// Change the value of some elements.
	linkedList[0] = 12;
	linkedList[3] = 27;
	linkedList.At(4) = 36;
	PrintLinkedList(linkedList);
	
	// Remove the head.
	linkedList.EraseAt(0);
	PrintLinkedList(linkedList);

	// Remove an element in the middle.
	linkedList.EraseAt(3);
	PrintLinkedList(linkedList);

	// Remove elements that match the values.
	linkedList.Erase(7);
	PrintLinkedList(linkedList);

	linkedList.Erase(9);
	PrintLinkedList(linkedList);

	linkedList.Erase(3);
	PrintLinkedList(linkedList);

	// Add 5 more elements to the linked list.
	linkedList.PushBack(4);
	linkedList.PushBack(4);
	linkedList.PushBack(2);
	linkedList.PushBack(3);
	linkedList.PushBack(1);
	PrintLinkedList(linkedList);

	linkedList.Insert(16, 0);
	PrintLinkedList(linkedList);

	linkedList.Insert(12, 3);
	PrintLinkedList(linkedList);

	linkedList.Insert(14, 9);
	PrintLinkedList(linkedList);

	linkedList.Insert(56, 20);
	PrintLinkedList(linkedList);

	// Check if the linked list contains values.
	int value1 = 3;
	std::cout << "The vector " << (linkedList.Contains(value1) ? "contains " : "does not contain ") << value1 << std::endl;
	std::cout << "Value " << value1 << " is first found at element " << linkedList.Find(value1) << std::endl;
	std::cout << std::endl;

	int value2 = 8;
	std::cout << "The vector " << (linkedList.Contains(value2) ? "contains " : "does not contain ") << value2 << std::endl;
	std::cout << "Value " << value2 << " is first found at element " << linkedList.Find(value2) << std::endl;
	std::cout << std::endl;

	// Clear all the elements.
	linkedList.Clear();
	PrintLinkedList(linkedList);
}

int main()
{	
	/*
	// Test vector RAII.
	{
		TestVectorRAII();
	}
	std::cin.get();
	*/

	/*
	// Test vector.
	{
		TestVector();
	}
	std::cin.get();
	*/

	// Test linked list RAII.
	{
		TestLinkedListRAII();
	}
	std::cin.get();

	/*
	// Test linked list.
	{
		TestLinkedList();
	}
	std::cin.get();
	*/
}