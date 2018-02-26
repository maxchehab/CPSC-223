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

// opens the Input.dat file
// pre: Input.dat file exists
// post: input file is opened OR program is exited
// usage: openInputFile(infile);
void openInputFile(ifstream &infile);

// takes the input file and reads one tree node from the infile
// pre: infile must be opened
//		infile pointer is at the beginning of a line
//		each item is on its own line
//		the left and right indices are bellow each item
//		ex:
// 		1111111 Item 1
// 		-1 -1
// post: newItem will contain a new Item and left and right will contain
//		their respective tree indices.
// 		infiles pointer is after the newline following the 2nd line
// usage: readOneTreeNode(inputFile, item, left, right);
void readOneTreeNode(ifstream &infile, Item &newItem, int &left, int &right);

// reads an entire tree
// pre: infile is open
//		the first line has the number of nodes to be read
//		infile has next item on a line
//		the next line are the two integers for the children
//		Example:
//		2
// 		1111111 Item 1
// 		-1 -1
//	post: BinaryTree is populated with Items from infile
// 		infiles pointer is after the newline following the
//		last set of children
//  usage: readTreeNodesAndInsert(infile, tree);
void readTreeNodesAndInsert(ifstream &infile, BinaryTree &tree);

// traverses and prints tree
// pre: BinaryTree is populated and exists
// post: In order, post order, and pre order
//		traversals are displayed
// usage: traverseAndPrintTree(tree);
void traverseAndPrintTree(BinaryTree &tree);

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

// traverses and prints tree
// pre: BinaryTree is populated and exists
// post: In order, post order, and pre order
//		traversals are displayed
// usage: traverseAndPrintTree(tree);
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

// opens the Input.dat file
// pre: Input.dat file exists
// post: input file is opened OR program is exited
// usage: openInputFile(infile);
void openInputFile(ifstream &infile)
{
	infile.open("Input.dat");
	if (infile.fail())
	{
		cout << "ERROR in opening Input.dat!!!" << endl;
		exit(1);
	}
}

// takes the input file and reads one tree node from the infile
// pre: infile must be opened
//		infile pointer is at the beginning of a line
//		each item is on its own line
//		the left and right indices are bellow each item
//		ex:
// 		1111111 Item 1
// 		-1 -1
// post: newItem will contain a new Item and left and right will contain
//		their respective tree indices.
// 		infiles pointer is after the newline following the 2nd line
// usage: readOneTreeNode(inputFile, item, left, right);
void readOneTreeNode(ifstream &infile, Item &newItem, int &left, int &right)
{
	char newLine;

	infile >> newItem;
	infile >> left;
	infile >> right;
	infile.get(newLine);
}

// reads an entire tree
// pre: infile is open
//		the first line has the number of nodes to be read
//		infile has next item on a line
//		the next line are the two integers for the children
//		Example:
//		2
// 		1111111 Item 1
// 		-1 -1
//	post: BinaryTree is populated with Items from infile
// 		infiles pointer is after the newline following the
//		last set of children
//  usage: readTreeNodesAndInsert(infile, tree);
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