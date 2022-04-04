#include "BinaryTree.h"
#include <iostream>

void PrintBinaryTreeInfo(BinaryTree<int>& binaryTree)
{

}

int main()
{
	BinaryTree<int> binaryTree;

	binaryTree.Insert(7);
	binaryTree.Insert(6);
	binaryTree.Insert(9);
	binaryTree.Insert(1);
	binaryTree.Insert(4);

	int valueToCheck = 4;
	std::cout << "The binary tree " << (binaryTree.Contains(valueToCheck) ? "contains value " : "does not contain value ") << valueToCheck << std::endl;

	binaryTree.PrintInOrder();

	binaryTree.Clear();

	std::cout << binaryTree.Size();
}