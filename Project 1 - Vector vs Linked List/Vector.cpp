#include <stdexcept>
#include "Vector.h"

template<class T>
Vector<T>::Vector(): arr(new T[1]), capacity(1), size(0)
{
}

template<class T>
Vector<T>::~Vector()
{
	delete[] arr;
}

template<class T>
void Vector<T>::PushFront(T newElement)
{
	if (size == capacity)
	{
		Reserve(capacity + 1);
	}

	for (int i = size - 1; i >= 0; --i)
	{
		arr[i + 1] = arr[i];
	}

	arr[0] = newElement;

	size++;
}

template<class T>
void Vector<T>::PushBack(T newElement)
{
	if (size == capacity)
	{
		Reserve(capacity + 1);
	}

	arr[size] = newElement;

	size++;
}

template<class T>
T& Vector<T>::operator[](int index)
{
	return At(index);
}

template<class T>
T& Vector<T>::At(int index)
{
	if (index < 0 || index >= size)
		throw std::invalid_argument("The index is invalid.");

	return arr[index];
}

template<class T>
int Vector<T>::Size()
{
	return size;
}

template<class T>
void Vector<T>::Reserve(int newCapacity)
{
	if (newCapacity > capacity)
	{
		// Create a new array.
		T* newArr = new T[newCapacity];

		// Copy elements from the old element to the new one.
		for (int i = 0; i < size; ++i)
		{
			newArr[i] = arr[i];
		}

		// Remove the old array.
		delete[] arr;

		// Reference the new array.
		arr = newArr;

		// Set the capacity.
		capacity = newCapacity;
	}
}

template<class T>
int Vector<T>::GetCapacity()
{
	return capacity;
}

template<class T>
void Vector<T>::EraseAt(int index)
{
	if (index < 0 || index >= size)
		return;

	for (int i = index; i < size - 1; ++i)
	{
		arr[i] = arr[i + 1];
	}

	size--;
}

template<class T>
void Vector<T>::Erase(T value)
{
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] == value)
		{
			EraseAt(i);
			return;
		}
	}
}

template<class T>
int Vector<T>::Find(T value)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			return i;
		}
	}

	return -1;
}

template<class T>
bool Vector<T>::Contains(T value)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			return true;
		}
	}

	return false;
}

template<class T>
void Vector<T>::Insert(T element, int index)
{
	if (index == 0)
	{
		PushFront(element);
		return;
	}
	
	// TODO: Handle the situation when the index is not at 0.

}

template<class T>
void Vector<T>::Resize(int newSize)
{
	if (newSize < 0)
		throw std::invalid_argument("The size must not be negative.");

	if (newSize > capacity)
	{
		Reserve(newSize);
	}

	// TODO: Add code here



}

template class Vector<int>;
