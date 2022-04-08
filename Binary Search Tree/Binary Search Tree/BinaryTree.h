// BinaryTree.h
// Programmer: Khoi Ho

#pragma once

#include <iostream>

class BinaryTree
{
private:
	struct Node
	{
		int value;
		Node* left;
		Node* right;

		Node();
		Node(const int& value);
	};

	Node* root;
	int size;

public:
	
	// Default constructor
	BinaryTree();

	// Copy constructor
	BinaryTree(const BinaryTree& other);

	// Destructor
	~BinaryTree();

	// Assignment operator.
	BinaryTree& operator=(const BinaryTree& other);

	// Insert a value to the tree.
	void Insert(const int& value);

	// Check if the tree contains a value.
	bool Contains(const int& value);

	// Remove a node that contains the specified value.
	void Erase(const int& value);

	// Remove all nodes.
	void Clear();

	// Get the size of the tree.
	int Size() const;

	// Pre-order traversal (root, left, right).
	void PrintPreOrder() const;

	// In-order traversal (left, root, right).
	void PrintInOrder() const;

	// Post-order traversal (left, right, root).
	void PrintPostOrder() const;
};
