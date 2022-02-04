// LinkedList.h
// Programmer: Khoi Ho

#pragma once

#include <stdexcept>

template<class T>
class Node
{
public:
	T value;
	Node<T>* next;

	Node(T aValue, Node<T>* aNext = nullptr);
};

template<class T>
inline Node<T>::Node(T aValue, Node<T>* aNext) : value(aValue), next(aNext) {}

template<class T>
class LinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	// Default constructor
	LinkedList();

	// Deallocates any memory the container needed to allocate
	~LinkedList();

	// Adds a single value to beginning of the container
	void PushFront(T value);

	// Adds a single value to end of the container
	void PushBack(T value);

	// Returns a reference to the element at the given index
	T& operator[](const int& index);

	// Return a reference to the element at the given index
	T& At(const int& index);

	// Get the head of the linked list.
	T& GetHead();

	// Get the tail of the linked list.
	T& GetTail();

	// Remove all elements from the list
	void Clear();

	// Returns the number of elements in this container
	int Size() const;

	// Removes the value at the given index, decreasing the contained size
	void EraseAt(const int& index);

	// Removes one value from the container: the first that matches
	void Erase(const T& value);

	// Returns the index of the given value, -1 if not found
	int Find(const T& value);

	// Returns true if this value is in the container
	bool Contains(const T& value);

	// Insert the given element at the given position. Position 0 should insert the element at the beginning of the container
	void Insert(const T& value, const int& index);
};

template<class T>
inline LinkedList<T>::LinkedList()
{
}

template<class T>
inline LinkedList<T>::~LinkedList()
{
	if (head != nullptr)
	{
		Node<T>* currentNode = head;

		while (currentNode->next != nullptr)
		{
			Node<T>* previousNode = currentNode;
			currentNode = currentNode->next;
			delete(previousNode);
		}

		delete currentNode;
	}
}

template<class T>
inline void LinkedList<T>::PushFront(T value)
{
	// Case 1: The linked list is empty.
	if (head == nullptr)
	{
		head = new Node<T>(value, nullptr);
		tail = head;
	}

	// Case 2: The linked list is not empty.
	else
	{
		head = new Node<T>(value, head);
	}

	size++;
}

template<class T>
inline void LinkedList<T>::PushBack(T value)
{
	// Case 1: The linked list is empty.
	if (head == nullptr)
	{
		head = new Node<T>(value, nullptr);
		tail = head;
	}

	// Case 2: The linked list is not empty.
	else
	{
		Node<T>* newNode = new Node<T>(value);
		tail->next = newNode;
		tail = newNode;
	}

	size++;
}

template<class T>
inline T& LinkedList<T>::operator[](const int& index)
{
	return At(index);
}

template<class T>
inline T& LinkedList<T>::At(const int& index)
{
	if (head == nullptr)
	{
		throw std::invalid_argument("The linked list contains no element.");
	}

	Node<T>* currentNode = head;
	int currentIndex = 0;
	
	while (currentIndex != index && currentNode != nullptr)
	{
		currentIndex++;
		currentNode = currentNode->next;
	}

	if (currentIndex == index && currentNode != nullptr)
	{
		return currentNode->value;
	}
	else
	{
		throw std::invalid_argument("The index exceeds the size of the linked list.");
	}
}

template<class T>
inline T& LinkedList<T>::GetHead()
{
	if (head == nullptr)
	{
		throw std::exception("Cannot get the head since the linked list is empty.");
	}

	return head->value;
}

template<class T>
inline T& LinkedList<T>::GetTail()
{
	if (head == nullptr)
	{
		throw std::exception("Cannot get the tail since the linked list is empty.");
	}

	return tail->value;
}

template<class T>
inline void LinkedList<T>::Clear()
{
	if (head != nullptr)
	{
		Node<T>* currentNode = head;

		while (currentNode->next != nullptr)
		{
			Node<T>* previousNode = currentNode;
			currentNode = currentNode->next;
			delete(previousNode);
		}

		delete currentNode;
		
		head = nullptr;
		tail = nullptr;

		size = 0;
	}
}

template<class T>
inline int LinkedList<T>::Size() const
{
	return size;
}

template<class T>
inline void LinkedList<T>::EraseAt(const int& index)
{
	if (index < 0)
	{
		throw std::invalid_argument("The index must not be negative.");
	}

	if (index >= size)
	{
		throw std::invalid_argument("The index exceeds the size of the linked list.");
	}

	if (head == nullptr)
		return;

	// Case 1: The erased node is the head.
	if (index == 0)
	{
		Node<T>* newHead = head->next;
		delete head;
		head = newHead;

		if (newHead == nullptr)
		{
			tail = nullptr;
		}

		--size;
	}

	// Case 2: The erased node is after the head.
	else
	{
		Node<T>* previousNode = head;
		Node<T>* currentNode = head->next;	
		int currentIndex = 1;

		while (currentNode != nullptr && currentIndex != index)
		{	
			previousNode = currentNode;
			currentNode = currentNode->next;
			currentIndex++;
		}

		if (currentNode != nullptr && currentIndex == index)
		{
			if (currentNode == tail)
			{
				tail = nullptr;
			}

			previousNode->next = currentNode->next;
			delete(currentNode);

			--size;
		}
	}
}

template<class T>
inline void LinkedList<T>::Erase(const T& value)
{
	if (head == nullptr)
		return;

	// Case 1: The erased node is the head.
	if (head->value == value)
	{
		Node<T>* newHead = head->next;
		delete head;
		head = newHead;

		if (newHead == nullptr)
		{
			tail = nullptr;
		}

		--size;
	}

	// Case 2: The erased node is after the head.
	else
	{
		Node<T>* previousNode = head;
		Node<T>* currentNode = head->next;

		while (currentNode != nullptr && currentNode->value != value)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}

		if (currentNode != nullptr && currentNode->value == value)
		{
			if (currentNode == tail)
			{
				tail = previousNode;
			}

			previousNode->next = currentNode->next;
			delete(currentNode);

			--size;
		}
	}
}

template<class T>
inline int LinkedList<T>::Find(const T& value)
{
	if (head == nullptr)
		return -1;

	Node<T>* currentNode = head;
	int currentIndex = 0;

	// Keep traversing until the element is found or the last element is reached.
	while (currentNode!= nullptr && currentNode->value != value)
	{
		currentNode = currentNode->next;
		currentIndex++;
	}

	// If the element is found, return the index of that element.
	if (currentNode != nullptr && currentNode->value == value)
	{
		return currentIndex;
	}

	// Return -1 if the element cannot be found.
	return -1;
}

template<class T>
inline bool LinkedList<T>::Contains(const T& value)
{
	Node<T>* currentNode = head;

	while (currentNode != nullptr)
	{
		// If the current node matches the value, return true.
		if (currentNode->value == value)
		{
			return true;
		}

		// If not, move to the next node.
		currentNode = currentNode->next;
	}

	// Cannot find the node we need, so return false.
	return false;
}

template<class T>
inline void LinkedList<T>::Insert(const T& value, const int& index)
{
	if (index < 0)
	{
		throw std::invalid_argument("The index must not be negative.");
	}

	// Case 1: The element is inserted at the head of the linked list.
	else if (index == 0)
	{
		PushFront(value);
	}

	// Case 2: The element is inserted within the size of the linked list.
	else if (index < size)
	{
		Node<T>* previousNode = head;
		Node<T>* currentNode = head->next;

		for (int currentIndex = 1; currentIndex < index; currentIndex++)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}

		Node<T>* newNode = new Node<T>(value, currentNode);
		previousNode->next = newNode;

		size++;
	}

	// Case 3: The element is inserted at the end of the linked list.
	else if (index == size)
	{
		PushBack(value);
	}

	// Case 4: The element is outside the linked list.
	else
	{
		while (size < index)
		{
			PushBack(T());
		}

		PushBack(value);
	}
}
