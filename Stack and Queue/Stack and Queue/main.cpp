#include "LinkedList.h"
#include <iostream>
#include <string>

template <class T>
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

int main()
{
	// Test PopFront() (int)
	{
		LinkedList<int> myLinkedList;

		myLinkedList.PushBack(7);
		myLinkedList.PushBack(1);
		myLinkedList.PushBack(5);
		myLinkedList.PushBack(2);
		myLinkedList.PushBack(3);

		PrintLinkedList(myLinkedList);

		while (myLinkedList.Size() > 0)
		{
			int removedValue = myLinkedList.PopFront();
			std::cout << "Removed value : " << removedValue << std::endl;

			PrintLinkedList(myLinkedList);
		}
	}

	// Test PopFront() (string)
	{
		LinkedList<std::string> myLinkedList2;
		myLinkedList2.PushBack("Jack");
		myLinkedList2.PushBack("Aresh");
		myLinkedList2.PushBack("Carl");
		myLinkedList2.PushBack("David");
		myLinkedList2.PushBack("Smith");

		PrintLinkedList(myLinkedList2);

		while (myLinkedList2.Size() > 0)
		{
			std::string removedValue = myLinkedList2.PopFront();
			std::cout << "Removed value : " << removedValue << std::endl;

			PrintLinkedList(myLinkedList2);
		}
	}

	// Test PopBack() (int)
	{
		LinkedList<int> myLinkedList;

		myLinkedList.PushBack(7);
		myLinkedList.PushBack(1);
		myLinkedList.PushBack(5);
		myLinkedList.PushBack(2);
		myLinkedList.PushBack(3);

		PrintLinkedList(myLinkedList);

		while (myLinkedList.Size() > 0)
		{
			int removedValue = myLinkedList.PopBack();
			std::cout << "Removed value : " << removedValue << std::endl;

			PrintLinkedList(myLinkedList);
		}
	}

	// Test PopBack() (string)
	{
		LinkedList<std::string> myLinkedList2;
		myLinkedList2.PushBack("Jack");
		myLinkedList2.PushBack("Aresh");
		myLinkedList2.PushBack("Carl");
		myLinkedList2.PushBack("David");
		myLinkedList2.PushBack("Smith");

		PrintLinkedList(myLinkedList2);

		while (myLinkedList2.Size() > 0)
		{
			std::string removedValue = myLinkedList2.PopBack();
			std::cout << "Removed value : " << removedValue << std::endl;

			PrintLinkedList(myLinkedList2);
		}
	}
}