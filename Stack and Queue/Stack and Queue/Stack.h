#pragma once

#include "LinkedList.h"

template <class T>
class Stack : protected LinkedList<T>
{
public:
	// Default constructor
	Stack();

	// Adds a single value to beginning of the container.
	void Push(const T& value);

	// Removes the value at the beginning of the container and returns its value.
	T Pop();

	// Removes all elements from the container.
	void Clear();

	// Return the number of elements in the container.
	int Size();
};

template<class T>
inline Stack<T>::Stack()
{
}

template<class T>
inline void Stack<T>::Push(const T& value)
{
	PushFront(value);
}

template<class T>
inline T Stack<T>::Pop()
{
	return PopFront();
}

template<class T>
inline void Stack<T>::Clear()
{
	Clear();
}
