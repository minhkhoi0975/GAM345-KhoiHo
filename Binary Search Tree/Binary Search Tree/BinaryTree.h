#pragma once

template <class T>
class BinaryTree
{
private:
	struct Node
	{
		T value;
		Node* left;
		Node* right;

		Node() : value(T()), left(nullptr), right(nullptr)
		{
		}

		Node(const T& value): value(value), left(nullptr), right(nullptr)
		{
		}
	};

	Node* root;
	int size;

public:
	BinaryTree();

	void Insert(const T& value);
	void Contains(const T& value) const;
	void Erase(const T& value);
	void Clear();
	int Size() const;
	void PrintInOrder() const;

	// TODO: Discuss traversal.

};

template<class T>
inline BinaryTree<T>::BinaryTree() : root(nullptr), size(0)
{
}

template<class T>
inline void BinaryTree<T>::Insert(const T& value)
{
	// Case 1: The root node is null.
	if (root == nullptr)
	{
		root = new Node(value);
		return;
	}

	// Case 2: The root node is not null.
	Node currentNode = root;
}
