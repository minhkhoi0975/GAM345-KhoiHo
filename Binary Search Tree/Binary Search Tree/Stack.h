// Stack.h
// Programmer: Khoi Ho

#pragma once

#include "LinkedList.h"

template <class T>
class Stack: protected LinkedList<T>
{
public:
	// Default constructor
	Stack();

	// Copy constructor
	Stack(const Stack<T>& other);

	// Adds a single value to the end of the container.
	void Push(const T& value);

	// Removes the value at the beginning of the container and returns its value.
	T Pop();

	// Removes all elements from the container.
	void Clear();

	// Return the number of elements in the container.
	int Size();
};

template<class T>
inline Stack<T>::Stack() : LinkedList<T>()
{
}

template<class T>
inline Stack<T>::Stack(const Stack<T>& other) : LinkedList<T>(other)
{
}

template<class T>
inline void Stack<T>::Push(const T& value)
{
	LinkedList<T>::PushFront(value);
}

template<class T>
inline T Stack<T>::Pop()
{
	return LinkedList<T>::PopFront();
}

template<class T>
inline void Stack<T>::Clear()
{
	LinkedList<T>::Clear();
}

template<class T>
inline int Stack<T>::Size()
{
	return LinkedList<T>::Size();
}
