//file TreeNode.cpp
//author Max Chehab and Kevin Shaw
//date 2/28/2018

//ADT TreeNode for a binary tree: data object a node with
//                            an item and a pointer to left and right children
// operations: constructors

// Especially designed for the BinaryTree class
#include "TreeNode.h"

//pre: nothing
//post: assigns right and left child no be nothing
//usage: TreeNode myTree();
TreeNode::TreeNode()
{
    leftChild = nullptr;
    rightChild = nullptr;
}

//pre: item is populated, theLeft and theRight pointers point to a
//      treenode or nullptr
//post: Populates treenode with the provided new item, and left and right
//      child treenode pointers
//usage: TreeNode myTree(myItem, leftItemPointer, rightItemPointer);
TreeNode::TreeNode(const Item &newItem, TreeNode *theLeft, TreeNode *theRight)
{
    item = newItem;
    leftChild = theLeft;
    rightChild = theRight;
}
