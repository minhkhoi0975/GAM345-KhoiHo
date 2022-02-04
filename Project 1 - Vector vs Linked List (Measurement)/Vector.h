// Vector.h
// Programmer: Khoi Ho

#pragma once

#include <stdexcept>

template<class T>
class Vector
{
private:
	T* arr;
	int capacity;
	int size;

public:

	// Default constructor.
	Vector();

	// Deallocates any memory the container needed to allocate
	~Vector();

	// Adds a single value to beginning of the container
	void PushFront(const T& newElement);

	// Adds a single value to end of the container
	void PushBack(const T& newElement);

	// Return a reference to the element at the given index
	T& operator[](const int& index);

	// Return a reference to the element at the given index
	T& At(const int& index);

	// Remove all elements from the list
	void Clear();

	// Returns the number of elements in this container
	int Size() const;

	// Allocates room for at least this many values. Does not shrink the storage
	void Reserve(const int& capacity);

	// Returns the amount of allocated space
	int GetCapacity() const;

	// Removes the value at the given index, decreasing the contained size
	void EraseAt(const int& index);

	// Removes one value from the container: the first that matches
    void Erase(const T& value);

	// Returns the index of the given value, -1 if not found
	int Find(const T& value) const;

	// Returns true if this value is in the container
	bool Contains(const T& value) const;

	// Insert the given element at the given position. Position 0 should insert the element at the beginning of the container.
	void Insert(const T& element, const int& index);

	// Adds or removes elements from the end of the container to achieve the given new size
	void Resize(const int& newSize);
};

template<class T>
inline Vector<T>::Vector() : arr(new T[1]), capacity(1), size(0) {}

template<class T>
inline Vector<T>::~Vector()
{
	delete[] arr;
}

template<class T>
inline void Vector<T>::PushFront(const T& newElement)
{
	// If the current size reaches the capacity, allocate more memory.
	if (size == capacity)
	{
		Reserve(capacity + 1);
	}

	// Move every value to the right.
	for (int i = size - 1; i >= 0; --i)
	{
		arr[i + 1] = arr[i];
	}

	// Assign the new value to the first element.
	arr[0] = newElement;

	++size;
}

template<class T>
inline void Vector<T>::PushBack(const T& newElement)
{
	// If the current size reaches the capacity, allocate more memory.
	if (size == capacity)
	{
		Reserve(capacity + 1);
	}

	// Assign the new value to the last element.
	arr[size] = newElement;

	++size;
}

template<class T>
inline T& Vector<T>::operator[](const int& index)
{
	return At(index);
}

template<class T>
inline T& Vector<T>::At(const int& index)
{
	if (index < 0)
	{
		throw std::invalid_argument("The index must be negative.");
	}
	else if (index >= size)
	{
		throw std::invalid_argument("The index must not exceed the size of the vector.");
	}

	return arr[index];
}

template<class T>
inline void Vector<T>::Clear()
{
	size = 0;
}

template<class T>
inline int Vector<T>::Size() const
{
	return size;
}

template<class T>
inline void Vector<T>::Reserve(const int& newCapacity)
{
	// Cannot reserve if the capacity is not a positive number.
	if (newCapacity <= 0)
	{
		throw std::invalid_argument("The capacity must be a positive number.");
	}

	// Only reserve if the new capacity is greater than the current capacity.
	if (newCapacity > capacity)
	{
		// Create a new array.
		T* newArr = new T[newCapacity];

		// Copy elements from the old array to the new one.
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
inline int Vector<T>::GetCapacity() const
{
	return capacity;
}

template<class T>
inline void Vector<T>::EraseAt(const int& index)
{
	// Cannot erase the element if the index is less than 0.
	if (index < 0)
	{
		throw std::invalid_argument("The index must not be negative.");
	}

	// Cannot erase the element if the index exceeds the size of the vector.
	if (index >= size)
	{
		throw std::invalid_argument("The index must not exceed the size of the vector.");
	}

	// Starting from the element right after the removed element, move the values to the left.
	for (int i = index; i < size; ++i)
	{
		arr[i] = arr[i + 1];
	}

	--size;
}

template<class T>
inline void Vector<T>::Erase(const T& value)
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
inline int Vector<T>::Find(const T& value) const
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
inline bool Vector<T>::Contains(const T& value) const
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
inline void Vector<T>::Insert(const T& element, const int& index)
{
	// Cannot insert the new element to the vector if the index is negative.
	if (index < 0)
	{
		throw std::invalid_argument("The index must not be negative.");
	}

	// Case 1: The index is 0. 
	else if (index == 0)
	{
		PushFront(element);
	}

	// Case 2: The index is within the size of the vector.
	else if (index > 0 && index < size)
	{
		if (size == capacity)
		{
			Reserve(capacity + 1);
		}

		++size;

		for (int i = size - 1; i >= index; --i)
		{
			arr[i] = arr[i - 1];
		}

		arr[index] = element;
	}

	// Case 3: The index is equal to the size of the vector.
	else if (index == size)
	{
		PushBack(element);
	}

	// Case 4: The index is greater than the size of the vector.
	else
	{
		// Resize the vector.
		Resize(index + 1);

		// Set the value of the last element.
		arr[index] = element;
	}
}

template<class T>
inline void Vector<T>::Resize(const int& newSize)
{
	// Cannot resize the vector if the new size is negative.
	if (newSize < 0)
	{
		throw std::invalid_argument("The size must not be negative.");
	}

	// The function does nothing if the size remains unchanged.
	if (newSize == size)
	{
		return;
	}

	// If the new size is lower than the current size, simply change size.
	else if (newSize < size)
	{
		size = newSize;
	}

	// If the new size is greater than the current size:
	// + Reserve the vector if the new size exceeds the capacity.
	// + Assign default value to new elements.
	else
	{
		if (newSize > capacity)
		{
			Reserve(newSize);
		}

		for (int i = size; i < newSize; i++)
		{
			arr[i] = T();
		}

		size = newSize;
	}
}