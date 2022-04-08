#include "BinaryTree.h"
#include <iostream>

void PrintBinaryTreeInfo(const BinaryTree& binaryTree)
{
	std::cout << "Size: " << binaryTree.Size() << std::endl;

	std::cout << "Pre-order Traversal: ";
	binaryTree.PrintPreOrder();

	std::cout << "In-order Traversal: ";
	binaryTree.PrintInOrder();

	std::cout << "Post-order Traversal: ";
	binaryTree.PrintPostOrder();

	std::cout << std::endl;
}

int main()
{
	// Test Destructor.
	/*
	{
		BinaryTree binaryTree;

		for (int i = 0; i < 100000; ++i)
		{
			binaryTree.Insert(i);
			std::cout << "Element " << i << " has been inserted." << std::endl;
		}
	}
	std::cin.get();
	*/

	/*
	// Test copy constructor.
	{
		BinaryTree binaryTree1;
		binaryTree1.Insert(100);
		binaryTree1.Insert(20);
		binaryTree1.Insert(200);
		binaryTree1.Insert(10);
		binaryTree1.Insert(30);
		binaryTree1.Insert(150);
		binaryTree1.Insert(300);

		//			 100
		//       |          |
		//      20         200
		//   |      |    |     |
		//  10      30  150    300
		
		BinaryTree binaryTree2(binaryTree1);
		PrintBinaryTree(binaryTree1);
		PrintBinaryTree(binaryTree2);

		// Make changes in binaryTree2 to check if binaryTree1 is changed.
		binaryTree2.Erase(100);
		binaryTree2.Erase(10);
		binaryTree2.Erase(30);

		PrintBinaryTree(binaryTree1);
		PrintBinaryTree(binaryTree2);

		// Assign binaryTree1 to binaryTree2.
		binaryTree2 = binaryTree1;
		binaryTree2.Erase(150);

		PrintBinaryTree(binaryTree1);
		PrintBinaryTree(binaryTree2);
	}
	*/

	// Test removing nodes.
	{
		BinaryTree binaryTree;
		binaryTree.Insert(100);
		binaryTree.Insert(20);
		binaryTree.Insert(200);
		binaryTree.Insert(10);
		binaryTree.Insert(30);
		binaryTree.Insert(150);
		binaryTree.Insert(300);

		//			 100
		//       |          |
		//      20         200
		//   |      |    |     |
		//  10      30  150    300
		PrintBinaryTreeInfo(binaryTree);

		// Remove a node that does not exist.
		binaryTree.Erase(40);

		//			 100
		//       |          |
		//      20         200
		//   |      |    |     |
		//  10      30  150    300
		PrintBinaryTreeInfo(binaryTree);

		// Remove a leaf node.
		binaryTree.Erase(30);

		//			 100
		//       |          |
		//      20         200
		//   |           |     |
		//  10         150    300
		PrintBinaryTreeInfo(binaryTree);

		// Remove a node with 1 child only.
		binaryTree.Erase(20);

		//			 100
		//       |          |
		//      10         200
		//               |     |
		//              150    300
		PrintBinaryTreeInfo(binaryTree);

		// Remove a node with 2 children.
		binaryTree.Erase(200);

		//			 100
		//       |          |
		//      10         150
		//                     |
		//                    300
		PrintBinaryTreeInfo(binaryTree);

		// Remove the root.
		binaryTree.Erase(100);

		//			 10
		//                |
		//               150
		//                    |
		//                   300
		PrintBinaryTreeInfo(binaryTree);
	}

	
	// Test clearing a binary tree.
	/*
	{
		BinaryTree binaryTree;

		binaryTree.Insert(100);						//			 100
		binaryTree.Insert(20);						//       |          |
		binaryTree.Insert(200);						//      20         200
		binaryTree.Insert(10);						//   |      |    |     |
		binaryTree.Insert(30);						//  10      30  150    300
		binaryTree.Insert(150);
		binaryTree.Insert(300);

		PrintBinaryTree(binaryTree);

		binaryTree.Clear();

		PrintBinaryTree(binaryTree);
	}
	*/
}