// BinaryTree.cpp
// Programmer: Khoi Ho
// Credits: 
// + Daniel Y. Liang for the erase algorithm (Introduction to Java - Programming and Data Structures).
// + GeeksForGeeks for the iterative in-order and post-order traversal algorithms:
//   - In-order traversal: https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
//	 - Post-order traversal:https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
#include "BinaryTree.h"
#include "Stack.h"

BinaryTree::Node::Node() : value(0), left(nullptr), right(nullptr)
{
}

BinaryTree::Node::Node(const int& value) : value(value), left(nullptr), right(nullptr)
{
}

BinaryTree::BinaryTree() : root(nullptr), size(0)
{
}

// Use pre-order traversal to copy the binary tree.
BinaryTree::BinaryTree(const BinaryTree& binaryTree): root(nullptr), size(0)
{
	if (binaryTree.root == nullptr)
	{
		return;
	}

	// Use this stack to keep track of all the nodes that need to be printed.
	Stack<Node*> stack;

	stack.Push(binaryTree.root);

	while (stack.Size() > 0)
	{
		// Pop out the node to be printed out.
		Node* currentNode = stack.Pop();

		// We push the right child node first before the left child node because we want to print out the left node first.
		if (currentNode->right != nullptr)
		{
			stack.Push(currentNode->right);
		}
		if (currentNode->left != nullptr)
		{
			stack.Push(currentNode->left);
		}

		// Insert the current value to the new binary tree.
		Insert(currentNode->value);
	}
}

BinaryTree::~BinaryTree()
{
	Clear();
}

// Use pre-order traversal to copy the binary tree.
BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
	// Clear all the current elements.
	Clear();

	if (other.root == nullptr)
	{
		return *this;
	}

	// Use this stack to keep track of all the nodes that need to be printed.
	Stack<Node*> stack;

	stack.Push(other.root);

	while (stack.Size() > 0)
	{
		// Pop out the node to be printed out.
		Node* currentNode = stack.Pop();

		// We push the right child node first before the left child node because we want to print out the left node first.
		if (currentNode->right != nullptr)
		{
			stack.Push(currentNode->right);
		}
		if (currentNode->left != nullptr)
		{
			stack.Push(currentNode->left);
		}

		// Insert the current value to the new binary tree.
		Insert(currentNode->value);
	}

	return *this;
}

void BinaryTree::Insert(const int& value)
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

bool BinaryTree::Contains(const int& value)
{
	Node* currentNode = root;

	while (currentNode != nullptr)
	{
		if (currentNode->value == value)
		{
			return true;
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

	return false;
}

// Erase() algorithm:
// I. Find the node to be removed and its parent.
// II.
//     1) If the removed node does not have left child.
//        + If the removed node is the root node, its right child is the new root.
//        + If the removed node is not the root node, link its parent to its right child.
//     2) If the removed node has a left child.
//        + Get the node with the highest value on the left tree of the removed node.
//        + Replace the removed node with inherit node.
void BinaryTree::Erase(const int& value)
{
	// Get the node to be removed.
	Node* removedNodeParent = nullptr;
	Node* removedNode = root;

	while (removedNode != nullptr && removedNode->value != value)
	{
		if (value < removedNode->value)
		{
			removedNodeParent = removedNode;
			removedNode = removedNode->left;
		}
		else
		{
			removedNodeParent = removedNode;
			removedNode = removedNode->right;
		}
	}

	if (removedNode != nullptr)
	{
		// Case 1: The removed node has no left child.
		if (removedNode->left == nullptr)
		{
			// The removed node is the root? Its right child is the new root.
			if (removedNode == root)
			{
				root = removedNode->right;
			}
			// The removed node is the root? Link its parent to its right child.
			else
			{				
				if (removedNodeParent->left == removedNode)
				{
					removedNodeParent->left = removedNode->right;
				}
				else
				{
					removedNodeParent->right = removedNode->right;
				}
			}

			delete removedNode;
		}

		// Case 2: The removed node has a left child.
		else
		{
			// On the left tree of the removed node, find the node with the highest value. That node is the inherit node.
			Node* inheritNodeParent = removedNode;
			Node* inheritNode = removedNode->left;

			while (inheritNode->right != nullptr)
			{
				inheritNodeParent = inheritNode;
				inheritNode = inheritNodeParent->right;
			}

			// By "erasing" the removed node, we change its value to that of the inherit node.
			removedNode->value = inheritNode->value;

			// Detach the inherit node's parent from the inherit node.
			if (inheritNodeParent->left == inheritNode)
			{
				inheritNodeParent->left = inheritNode->left;
			}
			else
			{
				inheritNodeParent->right = inheritNode->left;
			}

			// Delete the inherit node.
			delete inheritNode;
		}

		// Reduce the size.
		--size;
	}
}

void BinaryTree::Clear()
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

	root = nullptr;
}

int BinaryTree::Size() const
{
	return size;
}

// Pre-order traversal algorithm:
// I. Create an empty stack.
// II. Push the root into the stack.
// III. While the stack is not empty:
//     1. Pop a node out of the stack.
//     2. Push the poped node's right child and left child into the stack.
//     3. Print out the poped node.
void BinaryTree::PrintPreOrder() const
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty." << std::endl;
		return;
	}

	// Use this stack to keep track of all the nodes that need to be printed out.
	Stack<Node*> stack;

	stack.Push(root);

	while (stack.Size() > 0)
	{
		// Pop out the node to be printed out.
		Node* currentNode = stack.Pop();

		// We push the right child node first before the left child node because we want to print out the left node first.
		if (currentNode->right != nullptr)
		{
			stack.Push(currentNode->right);
		}
		if (currentNode->left != nullptr)
		{
			stack.Push(currentNode->left);
		}

		// Print out the poped node.
		std::cout << currentNode->value << ' ';
	}

	std::cout << std::endl;
}

// In-order traversal algorithm:
// I. Create an empty stack.
// II. Set current node to the root.
// III. While the stack is not empty OR the current node is not null:
//      1. If the current node is not null: 
//            + Push the current node to the stack.
//            + Set the current node to its left child.
//      2. If the current node is null: 
//            + Pop out a node from the stack and print out its value.
//            + Set the current node to the popped node's right child.
void BinaryTree::PrintInOrder() const
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty." << std::endl;
		return;
	}

	// Use this stack to keep track of all the nodes that need to be printed out.
	Stack<Node*> stack;

	Node* currentNode = root;

	while (stack.Size() > 0 || currentNode != nullptr)
	{
		// Reach and push the leftest nodes to the stack.
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

// Post-order traversal algorithm:
// I. Create a temporary stack and an output stack.
// II. Push the root to the temp stack.
// III. While the temp stack is not empty:
//      1. Pop a node out of the temp stack and push it in the output stack.
//      2. Push the popped node's children into the temp stack.
// IV. While the output stack is not empty: Pop out a node and print its value.
void BinaryTree::PrintPostOrder() const
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty." << std::endl;
		return;
	}

	// Use tempStack to keep track of all the nodes that need to be printed out. Use outputStack for the output.
	Stack<Node*> tempStack, outputStack;

	tempStack.Push(root);

	while (tempStack.Size() > 0)
	{
		Node* currentNode = tempStack.Pop();

		outputStack.Push(currentNode);

		if (currentNode->left != nullptr)
		{
			tempStack.Push(currentNode->left);
		}

		if (currentNode->right != nullptr)
		{
			tempStack.Push(currentNode->right);
		}
	}

	// Print out the contents in outputStack.
	while (outputStack.Size() > 0)
	{
		std::cout << (outputStack.Pop()->value) << " ";
	}
	std::cout << std::endl;
}
