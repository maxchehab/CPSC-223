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

int main()
{
	ifstream infile;
	Item newItem;
	BinaryTree myTree;

	openInputFile(infile);
	readTreeNodesAndInsert(infile, myTree);

	cout << "Pre-Order Traversal: " << endl;
	myTree.preorder();

	cout << "In-Order Traversal: " << endl;
	myTree.inorder();

	cout << "Post-Order Traversal: " << endl;
	myTree.postorder();
}

void openInputFile(ifstream &infile)
{
	infile.open("Input.dat");
	if (infile.fail())
	{
		cout << "ERROR in opening Input.dat!!!" << endl;
		exit(1);
	}
}

void readOneTreeNode(ifstream &infile, Item &newItem, int &left, int &right)
{
	char newLine;

	infile >> newItem;
	infile >> left;
	infile >> right;
	infile.get(newLine);
}

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