//file BinarySearchTree.cpp
//author Max Chehab
//date october 16, 2013 modified on March 26, 2018

// Specification of ADT Binary Search Tree
//    Data object: A binary search tree T that is either empty or in the form
// you finish

//    Operations: (a scaled-down version)
//       insert, rebalance, remove, remove, inorder traverse
// Contract: Assumes the this class can access private data members of class Node.
//    Those data members are: Item item, Node* leftptr, Node* rightptr.
//    There is a constructor that allows caller to give item, left and right ptrs.

#include "BinarySearchTree.h"
#include "Item.h"
#include <fstream>

// Gets the item associated with the inorder successor of a treenode
//pre: treep is not nullptr
//post: newItem is equal to the inorder successor of the provided treenode.
//usage: getInorderSucessorItem(myTreenode->leftChild, newItem);
void getInorderSucessorItem(TreeNode *treep, Item &newItem);

//Removes a specified item from a treenode and it's children
//pre: The targetPhone exists.
//post: A treenode, representing the tree is returned with the item who's
//      phone matches the provided targetPhone removed.
//usage: root = removeHelper(root, targetPhone);
TreeNode *removeTreeNode(TreeNode *treep);

// Handles removal of specified tree node based on three conditions,
//  1) it is a leaf, it has one child, it has two children.
// pre: treep is not nullptr
// post: returns either nullptr, or a restructed tree.
// usage: TreeNode mytreenode = removeTreeNode(otherTreenode);
TreeNode *removeHelper(TreeNode *treep, const Key &targetPhone) throw(Exception);

using namespace std;

// traveres and outputs treenode in an inorder traversal
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

// attaches a new treenode into correct place of a provided treenode using the
//  binary search algorithm
//pre: item exists
//post: if an item of the same contents exists an exception will be thrown
//  if not, the returned treenode will contain the provided item within
//  its children.
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

// Gets the item associated with the inorder successor of a treenode
//pre: treep is not nullptr
//post: newItem is equal to the inorder successor of the provided treenode.
//usage: getInorderSucessorItem(myTreenode->leftChild, newItem);
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

// Handles removal of specified tree node based on three conditions,
//  1) it is a leaf, it has one child, it has two children.
// pre: treep is not nullptr
// post: returns either nullptr, or a restructed tree.
// usage: TreeNode mytreenode = removeTreeNode(otherTreenode);
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
    return nullptr;
}

//Removes a specified item from a treenode and it's children
//pre: The targetPhone exists.
//post: A treenode, representing the tree is returned with the item who's
//      phone matches the provided targetPhone removed.
//usage: root = removeHelper(root, targetPhone);
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

// Builds a treenode whos branches and leaves represent a provided input stream
//pre: The provided input file is open. The provided length represents
//     the number of items to be added.
//     The cursor of the input file is directly before an item
//post: A treenode is recreated using the data provided by the input file.
//usage: root = rebalanceHelper(cout, 7);
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
//will traverse the binary search tree using a binary search algorithm.
//      if the item is not found an exception will be thrown.
//pre: provided targetPhone exists
//post: the provided item will be populated with the found item or an exception will be thrown
//usage: searchHelper(root, targetPhone, item);
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

//Searches the binary search tree for a provide phone number.
//  Will throw exception if phone number not found.
//pre: The provided targetPhone has been created.
//post: If an item who's phone number matches targetPhone exists the provided item will be populated
//      else an exception will be thrown.
//      An exception will be thrown if there is not enough heap space.
//usage: myTree.insert (newItem);
void BinarySearchTree::search(const Key &targetPhone, Item &item) throw(Exception)
{
    searchHelper(root, targetPhone, item);
}

// inserts an item into the tree.
//pre: The provided item has been created.
//post: The tree inserts the provided item into the tree.
//      An exception will be thrown if there is not enough heap space.
//usage: myTree.insert (newItem);
void BinarySearchTree::insert(const Item &item) throw(Exception)
{
    root = insertHelper(root, item);
    numberOfItems++;
}

// Removes an item from the tree.
//pre: The provided targetPhone exists inside the tree. If not an exception will be thrown.
//post: The an item who's phone number matches targetPhone will be removed from the tree.
//usage: myTree.remove (targetPhone);
void BinarySearchTree::remove(const Key &targetPhone) throw(Exception)
{
    root = removeHelper(root, targetPhone);
    numberOfItems--;
}

// Constructs a tree from an input stream
//pre: The provided input file is open. The provided length represents
//     the number of items to be added.
//     The cursor of the input file is directly before an item
//     For example:
//     1000000 Emma Stach
//     1234566 Michale Jordan
//     1234567 Bob marley
//     2000000 Emma Wolfame
//     3000000 Max Chehab
//     4000000 Kevin Hart
//     5000000 Mason Delutri

//post: The tree is recreated using the data provided by the input file.
//usage: myTree.rebalance (inputFile, 7);
void BinarySearchTree::rebalance(ifstream &inputFile, const int length) throw(Exception)
{
    root = rebalanceHelper(inputFile, length);
    numberOfItems = length;
}

// Prints a list of the tree in an inorder traversal
//pre: The provided output stream is open.
//post: the tree is printed in a list style with the number of items first.
//usage: myTree.inorderTraverse (cout);
void BinarySearchTree::inorderTraverse(ostream &outputStream)
{
    outputStream << numberOfItems << endl;
    inorderHelper(outputStream, root);
}