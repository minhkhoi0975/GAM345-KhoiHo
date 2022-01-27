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
	void PushFront(T newElement);

	// Adds a single value to end of the container
	void PushBack(T newElement);

	// Return a reference to the element at the given index
	T& operator[](int index);

	// Return a reference to the element at the given index
	T& At(int index);

	//void Clear();

	// Returns the number of elements in this container
	int Size() const;

	// Allocates room for at least this many values. Does not shrink the storage
	void Reserve(int capacity);

	// Returns the amount of allocated space
	int GetCapacity() const;

	// Removes the value at the given index, decreasing the contained size
	void EraseAt(const int& index);

	// Removes one value from the container: the first that matches
    void Erase(T value);

	// Returns the index of the given value, -1 if not found
	int Find(const T& value) const;

	// Returns true if this value is in the container
	bool Contains(const T& value) const;

	// Insert the given element at the given position. Position 0 should insert the element at the beginning of the container.
	void Insert(T element, const int& index);

	// Adds or removes elements from the end of the container to achieve the given new size
	void Resize(int newSize);
};

template<class T>
inline Vector<T>::Vector() : arr(new T[1]), capacity(1), size(0)
{
}

template<class T>
inline Vector<T>::~Vector()
{
	delete[] arr;
}

template<class T>
inline void Vector<T>::PushFront(T newElement)
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
inline void Vector<T>::PushBack(T newElement)
{
	if (size == capacity)
	{
		Reserve(capacity + 1);
	}

	arr[size] = newElement;

	size++;
}

template<class T>
inline T& Vector<T>::operator[](int index)
{
	return At(index);
}

template<class T>
inline T& Vector<T>::At(int index)
{
	if (index < 0)
	{
		throw std::invalid_argument("The index is cannot be negative.");
	}
	else if (index >= size)
	{
		throw std::invalid_argument("The index cannot exceed the size of the vector.");
	}

	return arr[index];
}

template<class T>
inline int Vector<T>::Size() const
{
	return size;
}

template<class T>
inline void Vector<T>::Reserve(int newCapacity)
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
inline int Vector<T>::GetCapacity() const
{
	return capacity;
}

template<class T>
inline void Vector<T>::EraseAt(const int& index)
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
inline void Vector<T>::Erase(T value)
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
inline void Vector<T>::Insert(T element, const int& index)
{
	if (index < 0)
	{
		throw std::invalid_argument("The index must not be negative.");
	}

	if (index == 0)
	{
		PushFront(element);
		return;
	}

	if (index >= size)
	{
		Resize(index + 1);
		arr[index] = element;
	}
	else
	{
		if (size == capacity)
		{
			Reserve(capacity + 1);
		}

		size++;

		for (int i = size - 1; i >= index; --i)
		{
			arr[i] = arr[i - 1];
		}

		arr[index] = element;
	}
}

template<class T>
inline void Vector<T>::Resize(int newSize)
{
	if (newSize < 0)
	{
		throw std::invalid_argument("The size must not be negative.");
	}

	if (newSize == size)
		return;
	else if (newSize < size)
	{
		size = newSize;
	}
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