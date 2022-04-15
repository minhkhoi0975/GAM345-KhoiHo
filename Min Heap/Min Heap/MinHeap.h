#pragma once

#include<vector>

template<class T>
class MinHeap
{
private:
	std::vector<T> data;

	void BubbleDown()
	{
		int parent = 0;
		
		while (true)
		{
			int leftChild = 2 * parent + 1;
			int rightChild = 2 * parent + 2;

			int childToSwap = parent;

			if (leftChild < data.size() && data[leftChild] < data[parent])
			{
				childToSwap = leftChild;
			}
			if (rightChild < data.size() && data[rightChild] < data[childToSwap])
			{
				childToSwap = rightChild;
			}

			if (parent == childToSwap)
				break;

			std::swap(data[parent], data[childToSwap]);
			parent = childToSwap;
		}
	}

	void BubbleUp()
	{
		int child = data.size() - 1;

		// childLeft = 2 * parent + 1   -> parent = (childLeft - 1) / 2
		// childRight = 2 * parent + 2  -> parent = (childright - 2) / 2
		for (int parent = (child - 1) / 2; parent >= 0 && data[parent] > data[child]; parent = (child - 1) / 2)
		{
			std::swap(data[parent], data[child]);
			child = parent;
		}
	}

public:
	int Size()
	{
		return data.size();
	}

	T& Peek() const
	{
		if (data.size() == 0)
		{
			throw std::exception("Cannot remove the root of the heap: The heap is empty.");
		}

		return data[0];
	}

	void Insert(const T& value)
	{
		data.push_back(value);
		BubbleUp();
	}

	T Remove()
	{
		if (data.size() == 0)
		{
			throw std::exception("Cannot remove the root of the heap: The heap is empty.");
		}

		T result = data[0];

		// Remove root with the last element.
		data[0] = data[data.size() - 1];

		// Actually erase it.
		data.erase(data.begin() + (data.size() - 1));

		BubbleDown();
	}
};