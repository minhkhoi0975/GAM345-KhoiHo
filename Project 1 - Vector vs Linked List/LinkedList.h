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
inline Node<T>::Node(T aValue, Node<T>* aNext) : value(aValue), next(aNext)
{
}

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
	if (head == nullptr)
	{
		head = new Node<T>(value, nullptr);
		tail = head;
	}
	else
	{
		head = new Node<T>(value, head);
	}

	size++;
}

template<class T>
inline void LinkedList<T>::PushBack(T value)
{
	if (head == nullptr)
	{
		head = new Node<T>(value, nullptr);
		tail = head;
	}
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
			//--size;
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
		throw std::invalid_argument("The index must not be negative");
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
		else
		{
			throw std::invalid_argument("The index exceeds the size of the linked list.");
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
				tail = nullptr;
			}

			previousNode->next = currentNode->next;
			delete(currentNode);

			--size;
		}
		else
		{
			throw std::invalid_argument("The index exceeds the size of the linked list.");
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

	while (currentNode!= nullptr && currentNode->value != value)
	{
		currentNode = currentNode->next;
		currentIndex++;
	}

	if (currentNode != nullptr && currentNode->value == value)
	{
		return currentIndex;
	}

	return -1;
}
