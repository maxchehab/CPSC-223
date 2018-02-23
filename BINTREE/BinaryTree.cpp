//file BinaryTree.cpp
//author Max Chehab
//date February 13. 2018

//Specification of ADT Binary Tree
//     Data object: a binary tree which is either empty or
//                  in the form of     r
//                                  /    \
//                                TL     TR
//                  where TL and TR are binary trees
//     Data Structure: YOU DO

//     Operations: create, destroy, insert a new node,
//                 traversals: preorder, inorder, postorder
#include <iostream>
#include <sstream>
#include "BinaryTree.h"

using namespace std;

//creates an empty binary tree
//post an empty BinaryTree object exists
BinaryTree::BinaryTree()
{
    root = -1;
    numberOfItems = 0;
}

//releases a binary tree
//pre a BinaryTree object exists
//post the BinaryTree object no longer exists

BinaryTree::~BinaryTree()
{
    root = -1;
    numberOfItems = 0;
}

//inserts a new node into a binary tree
//pre BinaryTree object exists. newItem, left, right are assigned
//post a node containing newItem with children left and right
//     has been added to the BinaryTree object
//usage tree.insert(myItem, 1, 2);
void BinaryTree::insert(const Item &newItem, int left, int right)
{
    if (numberOfItems < MAXITEMS)
    {
        if (root == -1)
            root = 0;
        binaryTree[numberOfItems].setNode(newItem, left, right);
        numberOfItems++;
    }
}

//recursive helper
void preorderHelper(TreeNode tree[], int myroot)
{
    Item item;

    if (myroot >= 0)
    {
        tree[myroot].getItem(item);
        cout << item;

        preorderHelper(tree, tree[myroot].getLeftChild());
        preorderHelper(tree, tree[myroot].getRightChild());
    }
}

//performs a Pre-Order traversal of a binary tree
//pre BinaryTree object exists
//post the items of the BinaryTree object are printed in Pre-Order
//     with items separated by a semi-colon
//     There is a newline after the last one
//usage tree.preorder();
void BinaryTree::preorder()
{
    preorderHelper(binaryTree, root);
    cout << endl;
}

//recursive helper
void inorderHelper(TreeNode tree[], int myroot)
{
    Item item;

    if (myroot >= 0)
    {
        inorderHelper(tree, tree[myroot].getLeftChild());
        tree[myroot].getItem(item);
        cout << item;
        inorderHelper(tree, tree[myroot].getRightChild());
    }
}

//performs a In-Order traversal of a binary tree
//pre BinaryTree object exists
//post the items of the BinaryTree object are printed in In-Order
//     with items separated by a semi-colon
//     There is a newline after the last one
//usage tree.inorder();
void BinaryTree::inorder()
{
    inorderHelper(binaryTree, root);
    cout << endl;
}

//recursive helper
void postorderHelper(TreeNode tree[], int myroot)
{
    Item item;

    if (myroot >= 0)
    {
        postorderHelper(tree, tree[myroot].getLeftChild());
        postorderHelper(tree, tree[myroot].getRightChild());
        tree[myroot].getItem(item);
        cout << item;
    }
}

//performs a Post-Order traversal of a binary tree
//pre BinaryTree object exists
//post the items of the BinaryTree object are printed in Post-Order
//     with items separated by a semi-colon
//     There is a newline after the last one
//usage tree.postorder();
void BinaryTree::postorder()
{
    postorderHelper(binaryTree, root);
    cout << endl;
}

//calculates Max Depth of tree using Post-Order traversal
//pre TreeNode object exists
//post returns max depth of tree.
int calculateMaxDepth(TreeNode tree[], int myroot)
{
    if (myroot >= 0)
    {
        int leftDepth = calculateMaxDepth(tree, tree[myroot].getLeftChild());
        int rightDepth = calculateMaxDepth(tree, tree[myroot].getRightChild());

        if (leftDepth > rightDepth)
            return (leftDepth + 1);
        else
            return (rightDepth + 1);
    }
    return 0;
}

// Print helper recursivly prints tree using Post-Order traversal
// pre TreeNode exists, root is greater or equal to zero
//      depth is zero, maxDepth represents the max depth of the tree
//      lines exists
// post lines is populated with print data.
// note: I apologize, but I used a stringstream to achieve the specification
//      noted in the assignment document. I found it impossible to keep both
//      Items on the same line.
void printHelper(TreeNode tree[], int myroot, int depth, int maxDepth, stringstream (&lines)[MAXITEMS])
{
    Item item;

    if (myroot >= 0)
    {
        printHelper(tree, tree[myroot].getLeftChild(), depth + 1, maxDepth, lines);
        printHelper(tree, tree[myroot].getRightChild(), depth + 1, maxDepth, lines);
        tree[myroot].getItem(item);
        for (int i = 0; i < maxDepth - depth; i++)
        {
            lines[depth] << "       ";
        }
        lines[depth] << item;
        lines[depth].seekp(-1, std::ios_base::end); // Remove last character (end line)
    }
}

// Performs print of tree
// pre BinaryTree object must exist
// post tree is printed to the cout
void BinaryTree::print()
{
    int maxDepth = calculateMaxDepth(binaryTree, root);
    stringstream lines[MAXITEMS];

    printHelper(binaryTree, root, 0, maxDepth, lines);
    cout << "A Tree of Height " << maxDepth << endl;
    for (int i = 0; i < maxDepth; i++)
    {
        cout << endl
             << lines[i].str();
    }
    cout << endl;
}
