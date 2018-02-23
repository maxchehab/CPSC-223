//file Clientprogram.cpp
//author Max Chehab
//date February 22. 2018

//Specification of ADT Clientprogram
//     Data object: a testing program to display the
//				functionality of Binary Tree
//     Operations: traverseAndPrintTree, readOneTreeNode,
//					openInputFile, readTreeNodesAndInsert
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Item.h"
#include "BinaryTree.h"
#include "TreeNode.h"

using namespace std;
void openInputFile(ifstream &infile);
void readOneTreeNode(ifstream &infile, Item &newItem, int &left, int &right);
void readTreeNodesAndInsert(ifstream &infile, BinaryTree &tree);
void traverseAndPrintTree(BinaryTree &tree);

// Opens input file. Reads and traverses degenerate and normal tree
int main()
{
	ifstream infile;
	Item newItem;
	BinaryTree normalTree;
	BinaryTree degenerateTree;

	openInputFile(infile);

	readTreeNodesAndInsert(infile, normalTree);
	cout << "Full Tree: " << endl;
	traverseAndPrintTree(normalTree);

	readTreeNodesAndInsert(infile, degenerateTree);
	cout << "Degenerate Tree: " << endl;
	traverseAndPrintTree(degenerateTree);
}

// Traverses and prints a BinaryTree
void traverseAndPrintTree(BinaryTree &tree)
{
	tree.print();
	cout << "Pre-Order Traversal: " << endl;
	tree.preorder();

	cout << "In-Order Traversal: " << endl;
	tree.inorder();

	cout << "Post-Order Traversal: " << endl;
	tree.postorder();
}

// Opens and input file
void openInputFile(ifstream &infile)
{
	infile.open("Input.dat");
	if (infile.fail())
	{
		cout << "ERROR in opening Input.dat!!!" << endl;
		exit(1);
	}
}

// Reads a single tree node
void readOneTreeNode(ifstream &infile, Item &newItem, int &left, int &right)
{
	char newLine;

	infile >> newItem;
	infile >> left;
	infile >> right;
	infile.get(newLine);
}

// Reads a single tree node and inserts into Binary Tree
void readTreeNodesAndInsert(ifstream &infile, BinaryTree &tree)
{
	int numberOfNodes, left, right;
	char newLine;
	Item newItem;

	infile >> numberOfNodes;
	infile.get(newLine);

	for (int i = 0; i < numberOfNodes; i++)
	{
		readOneTreeNode(infile, newItem, left, right);
		tree.insert(newItem, left, right);
	}
}