//file BinarySearchTree.cpp
//author Max Chehab
//date october 16, 2013 mopdified on February 21, 2018

// Specification of ADT Binary Search Tree
//    Data object: A binary search tree T that is either empty or in the form
// you finish

//    Operations: (a scaled-down version)
//       create, destroy, copy, operator=,
//       traversals (preorder, inorder, postorder)
// Contract: Assumes the this class can access private data members of class Node.
//    Those data members are: Item item, Node* leftptr, Node* rightptr.
//    There is a constructor that allows caller to give item, left and right ptrs.

#include "BinarySearchTree.h"
#include "Item.h"
#include <fstream>

void getInorderSucessorItem(TreeNode *treep, Item &newItem);

TreeNode *removeTreeNode(TreeNode *treep);

TreeNode *removeHelper(TreeNode *treep, const Key &targetPhone) throw(Exception);

using namespace std;

//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the
//     in order. the items are separated by commas
//usage: inorder (mroot);
void inorderHelper(ostream &outputStream, TreeNode *treep)
{
    if (treep != nullptr)
    {
        inorderHelper(outputStream, treep->leftChild);
        outputStream << treep->item;
        inorderHelper(outputStream, treep->rightChild);
    }
}

TreeNode *insertHelper(TreeNode *treep, const Item &item) throw(Exception)
{
    if (treep == nullptr)
    {
        treep = new (nothrow) TreeNode(item, nullptr, nullptr);
        if (treep == nullptr)
        {
            throw Exception("Your computer ran out of memory.");
        }
    }
    else if (item == treep->item)
    {
        throw Exception("The provided phone number has already been stored inside of this tree.\nTry providing a different number.");
    }
    else if (item < treep->item)
    {
        treep->leftChild = insertHelper(treep->leftChild, item);
    }
    else
    {
        treep->rightChild = insertHelper(treep->rightChild, item);
    }
    return treep;
}

void getInorderSucessorItem(TreeNode *treep, Item &newItem)
{
    if (treep->leftChild == nullptr)
    {
        newItem = treep->item;
    }
    else
    {
        getInorderSucessorItem(treep->leftChild, newItem);
    }
}

TreeNode *removeTreeNode(TreeNode *treep)
{
    if (treep->leftChild == nullptr && treep->rightChild == nullptr)
    {
        delete treep;
        treep = nullptr;
        return treep;
    }
    else if ((treep->leftChild != nullptr && treep->rightChild == nullptr) ||
             (treep->rightChild != nullptr && treep->leftChild == nullptr))
    {
        TreeNode *tempPtr = (treep->leftChild != nullptr) ? treep->leftChild : treep->rightChild;
        delete treep;
        treep = nullptr;
        return tempPtr;
    }
    else
    {
        Item newItem;
        getInorderSucessorItem(treep->rightChild, newItem);
        treep = removeHelper(treep, newItem);
        treep->item = newItem;
        return treep;
    }
}

TreeNode *removeHelper(TreeNode *treep, const Key &targetPhone) throw(Exception)
{
    if (treep == nullptr)
    {
        throw Exception("The provided phone number is not inside of this tree.");
    }
    else if (targetPhone == treep->item)
    {
        return removeTreeNode(treep);
    }
    else if (targetPhone < treep->item)
    {
        TreeNode *tempPtr = removeHelper(treep->leftChild, targetPhone);
        treep->leftChild = tempPtr;
        return treep;
    }
    else
    {
        TreeNode *tempPtr = removeHelper(treep->rightChild, targetPhone);
        treep->rightChild = tempPtr;
        return treep;
    }
    return treep;
}

TreeNode *rebalanceHelper(ifstream &inputFile, int length) throw(Exception)
{
    if (length > 0)
    {
        TreeNode *leftChild = rebalanceHelper(inputFile, length / 2);

        Item item;
        inputFile >> item;
        TreeNode *treep = new (nothrow) TreeNode(item, leftChild, nullptr);
        if (treep == nullptr)
        {
            throw Exception("Your computer ran out of memory.");
        }

        treep->rightChild = rebalanceHelper(inputFile, (length - 1) / 2);

        return treep;
    }
    else
    {
        return nullptr;
    }
}

void searchHelper(TreeNode *treep, const Key &targetPhone, Item &item) throw(Exception)
{
    if (treep == nullptr)
    {
        throw Exception("The provided phone number is not inside of this tree.");
    }
    else if (targetPhone == treep->item)
    {
        item = treep->item;
    }
    else if (targetPhone < treep->item)
    {
        searchHelper(treep->leftChild, targetPhone, item);
    }
    else
    {
        searchHelper(treep->rightChild, targetPhone, item);
    }
}

void BinarySearchTree::search(const Key &targetPhone, Item &item) throw(Exception)
{
    searchHelper(root, targetPhone, item);
}

void BinarySearchTree::insert(const Item &item) throw(Exception)
{
    root = insertHelper(root, item);
    numberOfItems++;
}

void BinarySearchTree::remove(const Key &targetPhone) throw(Exception)
{
    root = removeHelper(root, targetPhone);
    numberOfItems--;
}

void BinarySearchTree::rebalance(ifstream &inputFile, const int length) throw(Exception)
{
    root = rebalanceHelper(inputFile, length);
    numberOfItems = length;
}

void BinarySearchTree::inorderTraverse(ostream &outputStream)
{
    outputStream << numberOfItems << endl;
    inorderHelper(outputStream, root);
}