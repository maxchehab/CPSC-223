//file TreeNode.h
//author Max Chehab and Kevin Shaw
//date 2/28/2018

//ADT TreeNode for a binary tree: data object a node with
//                            an item and a pointer to left and right children
// operations: constructors

// Especially designed for the BinaryTree class

//file BinaryTree.cpp
//author Max Chehab and Kevin Shaw
//date 2/28/2018

// Specification of ADT TreeNode
//data object: a binary tree which is a non linear data structure
//data structure: a linked binary tree
//operations: displayPretty, operator=, preorderTraversal,
//             postorderTraversal,  inorderTraversal,
//             makeTreeOne, makeTreeTwo

#ifndef NODE_H
#define NODE_H

#include <cstdlib>
#include "Item.h"
using namespace std;

class TreeNode
{
public:
  //pre: nothing
  //post: assigns right and left child no be nothing
  //usage: TreeNode myTree();
  TreeNode();

  //pre: item is populated, theLeft and theRight pointers point to a
  //      treenode or nullptr
  //post: Populates treenode with the provided new item, and left and right
  //      child treenode pointers
  //usage: TreeNode myTree(myItem, leftItemPointer, rightItemPointer);
  TreeNode(const Item &newItem, TreeNode *theLeft, TreeNode *theRight);

  Item item;
  TreeNode *leftChild;
  TreeNode *rightChild;
};
#endif
