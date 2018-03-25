//file BinarySearchTree.h
//author Max Chehab
//date october 16, 2013 mopdified on February 21, 2018

// Specification of ADT Binary Search Tree
//    Data object: A binary tree T that is either empty or in the form
// you finish

//    Operations: (a scaled-down version)
//       create, destroy, copy, operator=,
//       traversals (preorder, inorder, postorder)
// Contract: Assumes the this class can access private data members of class Node.
//    Those data members are: Item item, Node* leftptr, Node* rightptr.
//    There is a constructor that allows caller to give item, left and right ptrs.

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "BinaryTree.h"
#include "Exception.h"
#include <iostream>
using namespace std;

class BinarySearchTree : public BinaryTree
{
public:
  void search(const Key &targetPhone, Item &item) throw(Exception);

  void insert(const Item &item) throw(Exception);

  void remove(const Key &targetPhone) throw(Exception);

  void rebalance(ifstream &inputFile, const int length) throw(Exception);

  void inorderTraverse(ostream &outputStream);

  int numberOfItems;
};
#endif
