//file BinaryTree.cpp
//author Max Chehab and Kevin Shaw
//date 2/28/2018

// Specification of ADT BinaryTree
// Data object: A binary tree T that is either empty or in the form of
//
//                        bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//    Operations: (a scaled-down version)
//       create, destroy, copy, operator=,
//       traversals (preorder, inorder, postorder)
// Contract: Assumes the this class can access private data members of class Node.
//    Those data members are: Item item, Node* leftptr, Node* rightptr.
//    There is a constructor that allows caller to give item, left and right ptrs.

#include "BinaryTree.h"
#include <fstream>
using namespace std;

void destroyTree(TreeNode *&treep);

// ***************** recursive helpers *****************

//Copies one binary tree to another
//pre oldtreep points to the root of a binary tree
//post: newtreep points to the root of a binary tree
//  that has copies of the nodes of oldtreep's tree
//usage: copyTree (newptr, oldptr);
void copyTree(TreeNode *&newtreep, TreeNode *oldtreep) throw(Exception)
{
    if (newtreep != nullptr)
    {
        destroyTree(newtreep);
    }
    if (oldtreep == nullptr)
    {
        newtreep = nullptr;
    }
    else
    {
        //preorder traversals
        newtreep = new (nothrow) TreeNode(oldtreep->item, nullptr, nullptr);
        if (newtreep == nullptr)
        {
            throw Exception("operator=: no space in heap");
        }
        copyTree(newtreep->leftChild, oldtreep->leftChild);
        copyTree(newtreep->rightChild, oldtreep->rightChild);
    }
}

//Releases memory for a binary tree
//pre: treep points to the root of a binary tree
//post: releases all of the nodes in the tree pointed to by treep
//    and leaves treep empty.
//usage: destroyTree (mroot);
void destroyTree(TreeNode *&treep)
{
    if (treep != nullptr)
    {
        destroyTree(treep->leftChild);
        destroyTree(treep->rightChild);
        delete treep;
        treep = nullptr;
    }
}

// Print helper recursivly prints tree using In-Order traversal
// with a appended string
// pre: TreeNode exists
// post: Tree is printed to the provide output
// usage: writePretty(root, 0, "root->", output);
void writePretty(TreeNode *treep, int level, string append, ostream &output)
{
    if (treep != nullptr)
    {
        level++;
        writePretty(treep->rightChild, level, "    /", output);
        for (int i = 1; i < level; i++)
        {
            output << "     ";
        }
        output << append << treep->item << ":" << treep->balance << endl;
        writePretty(treep->leftChild, level, "    \\", output);
    }
}
// ********** recursive helpers for the traversals ****************
//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the
//     pre order. the items are separated by commas
//usage: preorder (mroot);
void preorder(TreeNode *treep)
{
    if (treep != nullptr)
    {
        cout << treep->item;
        preorder(treep->leftChild);
        preorder(treep->rightChild);
    }
}

//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the
//     in order. the items are separated by commas
//usage: inorder (mroot);
void inorder(ostream &outputStream, TreeNode *treep)
{
    if (treep != nullptr)
    {
        inorder(outputStream, treep->leftChild);
        outputStream << treep->item;
        inorder(outputStream, treep->rightChild);
    }
}

//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the
//     post order. the items are separated by commas
//usage: postorder (mroot);
void postorder(TreeNode *treep)
{
    if (treep != nullptr)
    {
        postorder(treep->leftChild);
        postorder(treep->rightChild);
        cout << treep->item;
    }
}

// **************************public methods************************

//creates an empty binary tree
//post: object is an empty binary tree
//usage: BinaryTree zags;
BinaryTree::BinaryTree()
{
    root = nullptr;
}

//creates a new binary tree that is a copy of an existing tree
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: BinaryTree zags (bulldog);
BinaryTree::BinaryTree(const BinaryTree &rightHandSideTree) throw(Exception)
{
    root = nullptr;
    copyTree(root, rightHandSideTree.root);
}

//releases the memory of a binary tree
//pre: object exists
//post: memory for the object has been released. object theoretically does not exist
//       but in practice, it is empty.
BinaryTree::~BinaryTree()
{
    destroyTree(root);
}

// ******************** member functions ********************************************
//@pre: binary tree object exists
// **********************************************************************************

//checks for an empty tree
//post: returns true if the object is empty; else returns false
//usage: if (tree.isEmpty())
bool BinaryTree::isEmpty() const
{
    return (root == nullptr);
}

//copies one tree to another
//pre: rightHandSideTree is an assigned tree.
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: atree = btree = ctree;
BinaryTree &BinaryTree::operator=(const BinaryTree &rightHandSideTree) throw(Exception)
{
    root = nullptr;
    copyTree(root, rightHandSideTree.root);
    return *this;
}

//prints the tree to look like a computer science tree
//post: outputs the tree as in the example below
//
//                        bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: tree.prettyDisplay();
void BinaryTree::prettyDisplay(ostream &output)
{
    writePretty(root, 0, "root ->", output);
}

// *************** on the following traversals
//pre: desired output stream is open.
//post: prints the objects in the tree in order specified
//usage: tree.preorderTraverse();
//similarly for the other traversals
// *****************************************************
void BinaryTree::preorderTraverse()
{
    preorder(root);
}

void BinaryTree::inorderTraverse(ostream &outputStream)
{
    inorder(outputStream, root);
}

void BinaryTree::postorderTraverse()
{
    postorder(root);
}

//makes a full binary tree of height 2
//pre input is either cin or an open file
//    input's pointer is before the first item
//post: object is a full binary tree of height 2
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: myTree.makeTreeOne(infile);
void BinaryTree::makeTreeOne(istream &input) throw(Exception)
{
    Item newguy;

    input >> newguy;
    root = new (nothrow) TreeNode(newguy, nullptr, nullptr);
    if (root == nullptr)
    {
        throw Exception("makeTreeOne: no room in the heap");
    }

    input >> newguy;
    root->leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
    if (root->leftChild == nullptr)
    {
        throw Exception("makeTreeOne: no room in the heap");
    }

    input >> newguy;
    root->rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
    if (root->rightChild == nullptr)
    {
        throw Exception("makeTreeOne: no room in the heap");
    }
}

//makes a complete but not full binary tree of height 3
//throws an exception if there is not enough room in the
//       heap to make the tree
//pre input is either cin or an open file
//    input's pointer is before the first item
//post: object is a complete binary tree of height 3
//usgage: myTree.makeTreeTwo(infile);

void BinaryTree::makeTreeTwo(istream &input) throw(Exception)
{
    Item newguy;

    input >> newguy;
    root = new (nothrow) TreeNode(newguy, nullptr, nullptr);
    if (root == nullptr)
    {
        throw Exception("makeTreeTwo: no room in the heap");
    }

    input >> newguy;
    TreeNode *child = new (nothrow) TreeNode(newguy, nullptr, nullptr);
    if (child == nullptr)
    {
        throw Exception("makeTreeTwo: no room in the heap");
    }

    input >> newguy;
    root->leftChild = new (nothrow) TreeNode(newguy, child, nullptr);
    if (root->leftChild == nullptr)
    {
        throw Exception("makeTreeTwo: no room in the heap");
    }
    input >> newguy;
    root->rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
    if (root->rightChild == nullptr)
    {
        throw Exception("makeTreeTwo: no room in the heap");
    }
    else
    {
        throw Exception("I am throwing an exception at you, Dr. Y. Do you have your catcher’s mitt ready?");
    }
}
