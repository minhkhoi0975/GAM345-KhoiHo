#pragma once

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
	int Size();

	// Allocates room for at least this many values. Does not shrink the storage
	void Reserve(int capacity);

	// Returns the amount of allocated space
	int GetCapacity();

	// Removes the value at the given index, decreasing the contained size
	void EraseAt(int index);

	// Removes one value from the container: the first that matches
    void Erase(T value);

	// Returns the index of the given value, -1 if not found
	int Find(T value);

	// Returns true if this value is in the container
	bool Contains(T value);

	// Insert the given element at the given position. Position 0 should insert the element at the beginning of the container.
	void Insert(T element, int index);

	// Adds or removes elements from the end of the container to achieve the given new size
	void Resize(int size);
};