#pragma once

#include <iostream>
#include "Stack.h"

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
#ifdef _DEBUG
			std::cout << "Node " << value << " is constructed." << std::endl;
#endif // DEBUG
		}

		Node(const T& value): value(value), left(nullptr), right(nullptr)
		{
#ifdef _DEBUG
			std::cout << "Node " << value << " is constructed." << std::endl;
#endif // DEBUG
		}

#ifdef _DEBUG
		~Node()
		{
			std::cout << "Node " << value << " is deleted." << std::endl;
		}
#endif // DEBUG
	};

	Node* root;
	int size;

	// Find the node that contains the value.
	Node* FindNode(const T& value)
	{
		Node* currentNode = root;

		while (currentNode != nullptr)
		{
			if (currentNode->value == value)
			{
				return currentNode;
			}
			else if (value < currentNode->value)
			{
				currentNode = currentNode->left;
			}
			else
			{
				currentNode = currentNode->right;
			}
		}

		return nullptr;
	}
	
	// Find the node that contains the value and its parent.
	Node* FindNode(const T& value, Node*& parent)
	{
		parent = nullptr;
		Node* currentNode = root;

		while (currentNode != nullptr)
		{
			if (currentNode->value == value)
			{
				return currentNode;
			}
			else if (value < currentNode->value)
			{
				parent = currentNode;
				currentNode = currentNode->left;
			}
			else
			{
				parent = currentNode;
				currentNode = currentNode->right;
			}
		}

		parent = nullptr;
		return nullptr;
	}

public:
	BinaryTree();

	// Insert a value to the tree.
	void Insert(const T& value);

	// Check if the tree contains a value.
	bool Contains(const T& value);

	// Remove a node that contains the specified value.
	void Erase(const T& value);

	// Remove all nodes.
	void Clear();

	// Get the size of the tree.
	int Size() const;

	// Print the values in-order.
	void PrintInOrder();

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
		size++;
		return;
	}

	// Case 2: The root node is not null.
	Node* currentNode = root;
	bool isInserted = false; // Used for checking if the new node has been inserted.

	while (!isInserted)
	{
		// If the new value is less than the current node's value, move to the left.
		if (value < currentNode->value)
		{
			if (currentNode->left == nullptr)
			{
				currentNode->left = new Node(value);
				size++;
				isInserted = true;
			}
			else
			{
				currentNode = currentNode->left;
			}
		}
		// If the new value is greater than or equal to the current node's value, move to the right.
		else
		{
			if (currentNode->right == nullptr)
			{
				currentNode->right = new Node(value);
				size++;
				isInserted = true;
			}
			else
			{
				currentNode = currentNode->right;
			}
		}
	}
}

template<class T>
inline bool BinaryTree<T>::Contains(const T& value)
{
	return BinaryTree<T>::FindNode(value) != nullptr;
}

template<class T>
inline void BinaryTree<T>::Erase(const T& value)
{
	// Get the node to be removed.
	Node* removedNodeParent;
	Node* removedNode = FindNode(value, removedNodeParent);

	if (removedNode != nullptr)
	{
		// Case 1: The removed node has no left child.
		if (removedNode->left == nullptr)
		{
			// Removed node is the root? Its right child is the new root.
			if (removedNode == root)
			{
				root = removedNode->right;
				delete removedNode;
			}
			else
			{
				// Parent node links to the removed node's right node.
				if (removedNodeParent->left == removedNode)
				{
					removedNodeParent->left = removedNode->right;
				}
				else
				{
					removedNodeParent->right = removedNode->right;
				}
				delete removedNode;
			}
		}

		// Case 2: The removed has a left child.
		else
		{
			// On the left tree of the removed node, find the node with the highest value.
			Node* inheritNodeParent = removedNode;
			Node* inheritNode = removedNode->left;

			while (inheritNode->right != nullptr)
			{
				inheritNodeParent = inheritNode;
				inheritNode = inheritNodeParent->right;
			}

			// By "deleting" the removed node, we change its value to that of the inherit node.
			removedNode->value = inheritNode->value;

			// Delete the inherit node.
			if (inheritNodeParent->left == inheritNode)
			{
				inheritNodeParent->left = inheritNode->left;
			}
			else
			{
				inheritNodeParent->right = inheritNode->left;
			}

			delete inheritNode;
		}

		// Reduce the size.
		--size;
	}
}

template<class T>
inline void BinaryTree<T>::Clear()
{
	if (root == nullptr)
		return;

	// Use this stack to keep track of all the nodes that need to be deleted.
	Stack<Node*> stack;

	stack.Push(root);

	while (stack.Size() > 0)
	{
		// Pop a node out of the stack.
		Node* deletedNode = stack.Pop();

		// Put the deleted node's children in the stack.
		if (deletedNode->left != nullptr)
		{
			stack.Push(deletedNode->left);
		}
		if (deletedNode->right != nullptr)
		{
			stack.Push(deletedNode->right);
		}

		// Delete the node.
		delete deletedNode;

		// Reduce the size.
		--size;
	}
}

template<class T>
inline int BinaryTree<T>::Size() const
{
	return size;
}

template<class T>
inline void BinaryTree<T>::PrintInOrder()
{
	if (root == nullptr)
		std::cout << "The tree is empty." << std::endl;

	// Use this stack to keep track of all the nodes that need to be printed.
	Stack<Node*> stack;

	Node* currentNode = root;

	while (stack.Size() > 0 || currentNode != nullptr)
	{
		// Reach and push the leftest node to the stack.
		if (currentNode != nullptr)
		{
			stack.Push(currentNode);
			currentNode = currentNode->left;
		}

		// If the current node is empty, pop a node out, print its value and move to its right node.
		else
		{
			currentNode = stack.Pop();
			std::cout << currentNode->value << " ";

			currentNode = currentNode->right;
		}
	}

	std::cout << std::endl;
}
