#include "Stack.h"
#include "Queue.h"
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

void TestLinkedListPushAndPop()
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

void TestStack()
{
	// Test integer stack.
	{
		Stack<int> stack1;

		// Push some elements into the stack.
		stack1.Push(7);
		stack1.Push(9);
		stack1.Push(4);
		stack1.Push(5);
		stack1.Push(3);
		stack1.Push(1);

		// Pop the elements and print them out.
		while (stack1.Size() > 0)
		{
			std::cout << stack1.Pop() << std::endl;
		}
		std::cout << std::endl;
	}

	// Test clearing an intenger stack.
	{
		Stack<int> stack2;

		// Push some elements into the queue.
		stack2.Push(7);
		stack2.Push(9);
		stack2.Push(4);
		stack2.Push(5);
		stack2.Push(3);
		stack2.Push(1);

		// Print out the size of the queue.
		std::cout << "Current size: " << stack2.Size() << std::endl;

		// Clear the queue.
		stack2.Clear();

		// Print out the size of the queue.
		std::cout << "Current size: " << stack2.Size() << std::endl;

		std::cout << std::endl;
	}

	// Test string stack.
	{
		Stack<std::string> stack3;

		// Push some elements into the stack.
		stack3.Push("Andrew");
		stack3.Push("Smith");
		stack3.Push("Carl");
		stack3.Push("Lara");
		stack3.Push("Joe");
		stack3.Push("Anna");

		// Pop the elements and print them out.
		while (stack3.Size() > 0)
		{
			std::cout << stack3.Pop() << std::endl;
		}
		std::cout << std::endl;
	}

	// Test clearing a string stack.
	{
		Stack<std::string> stack4;

		// Push some elements into the queue.
		stack4.Push("Anna");
		stack4.Push("Smith");
		stack4.Push("Lara");
		stack4.Push("Carl");

		// Print out the size of the queue.
		std::cout << "Current size: " << stack4.Size() << std::endl;

		// Clear the queue.
		stack4.Clear();

		// Print out the size of the queue.
		std::cout << "Current size: " << stack4.Size() << std::endl;

		std::cout << std::endl;
	}
}

void TestQueue()
{
	// Test pushing and poping an integer queue.
	{
		Queue<int> queue1;

		// Push some elements into the queue.
		queue1.Push(7);
		queue1.Push(9);
		queue1.Push(4);
		queue1.Push(5);
		queue1.Push(3);
		queue1.Push(1);

		// Pop the elements and print them out.
		while (queue1.Size() > 0)
		{
			std::cout << queue1.Pop() << std::endl;
		}
		std::cout << std::endl;
	}

	// Test clearing an intenger queue.
	{
		Queue<int> queue2;

		// Push some elements into the queue.
		queue2.Push(7);
		queue2.Push(9);
		queue2.Push(4);
		queue2.Push(5);
		queue2.Push(3);
		queue2.Push(1);

		// Print out the size of the queue.
		std::cout << "Current size: " << queue2.Size() << std::endl;

		// Clear the queue.
		queue2.Clear();

		// Print out the size of the queue.
		std::cout << "Current size: " << queue2.Size() << std::endl;

		std::cout << std::endl;
	}

	// Test pushing and poping a string stack.
	{
		Queue<std::string> queue3;

		// Push some elements into the queue.
		queue3.Push("Andrew");
		queue3.Push("Smith");
		queue3.Push("Carl");
		queue3.Push("Lara");
		queue3.Push("Joe");
		queue3.Push("Anna");

		// Pop the elements and print them out.
		while (queue3.Size() > 0)
		{
			std::cout << queue3.Pop() << std::endl;
		}
		std::cout << std::endl;
	}

	// Test clearing a string queue.
	{
		Queue<std::string> queue4;

		// Push some elements into the queue.
		queue4.Push("Anna");
		queue4.Push("Smith");
		queue4.Push("Lara");
		queue4.Push("Carl");

		// Print out the size of the queue.
		std::cout << "Current size: " << queue4.Size() << std::endl;

		// Clear the queue.
		queue4.Clear();

		// Print out the size of the queue.
		std::cout << "Current size: " << queue4.Size() << std::endl;

		std::cout << std::endl;
	}
}

int main()
{
	// TestLinkedListPushAndPop();
	TestStack();
	// TestQueue();
}