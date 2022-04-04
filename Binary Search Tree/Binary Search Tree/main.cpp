#include "BinaryTree.h"
#include <iostream>

void PrintBinaryTreeInfo(BinaryTree<int>& binaryTree)
{

}

int main()
{
	BinaryTree<int> binaryTree;

	binaryTree.Insert(100);						//			   100
	binaryTree.Insert(20);						//       |          |
	binaryTree.Insert(200);						//      20         200
	binaryTree.Insert(10);						//   |      |    |     |
	binaryTree.Insert(30);						//  10      30  150    300
	binaryTree.Insert(150);
	binaryTree.Insert(300);

	std::cout << "Tree size: " << binaryTree.Size() << std::endl;

	int valueToCheck = 10;
	std::cout << "The binary tree " << (binaryTree.Contains(valueToCheck) ? "contains value " : "does not contain value ") << valueToCheck << std::endl;

	int valueToCheck2 = 40;
	std::cout << "The binary tree " << (binaryTree.Contains(valueToCheck2) ? "contains value " : "does not contain value ") << valueToCheck2 << std::endl;

	std::cout << "Pre-order Traversal: ";
	binaryTree.PrintPreOrder();

	std::cout << "In-order Traversal: ";
	binaryTree.PrintInOrder();

	binaryTree.Clear();

	std::cout << "Tree size: " << binaryTree.Size() << std::endl;
}