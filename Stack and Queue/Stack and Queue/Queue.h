// Queue.h
// Programmer: Khoi Ho

#pragma once

#include "LinkedList.h"

template <class T>
class Queue : protected LinkedList<T>
{
public:
	// Default constructor
	Queue();

	// Adds a single value to the beginning of the container.
	void Push(const T& value);

	// Removes the value at the beginning of the container and returns its value.
	T Pop();

	// Removes all elements from the container.
	void Clear();

	// Return the number of elements in the container.
	int Size();
};

template<class T>
inline Queue<T>::Queue() : LinkedList<T>()
{
}

template<class T>
inline void Queue<T>::Push(const T& value)
{
	LinkedList<T>::PushBack(value);
}

template<class T>
inline T Queue<T>::Pop()
{
	return LinkedList<T>::PopFront();
}

template<class T>
inline void Queue<T>::Clear()
{
	LinkedList<T>::Clear();
}

template<class T>
inline int Queue<T>::Size()
{
	return LinkedList<T>::Size();
}