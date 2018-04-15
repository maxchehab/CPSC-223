#include "AVLTree.h"

const int MAXHEIGHT = 10;

struct SearchPath
{
    TreeNode *path[MAXHEIGHT];
    int pathSize;
    int pivotIndex;
    SearchPath();
};

SearchPath::SearchPath()
{
    pathSize = 0;
    pivotIndex = 0;
    for (int k = 0; k < MAXHEIGHT; k++)
    {
        path[k] = nullptr;
    }
}

//Evan Swanson, Ryan Hays, Patrick Seminatore, Mason Dellutri, and Dr. Y

//Inserts a new item and assigns the search path and its size
//Pre: newitem has been assigned. treeptr is assigned root or
//     assigned another pointer in the AVL tree along the search path
//Post: if newitem's phone number is not already in the tree, then
//      newitem has been placed as in binary search tree and
//    search's pathSize is the number of nodes in the path and
//    search's path has been assigned to all the nodes in the search path
//Usage: BSTinsertAndMakeSearchPath(newitem, root, search);
void BSTinsertAndMakeSearchPath(const Item &newitem, TreeNode *&treeptr, SearchPath &search) throw(Exception)
{
    search.path[search.pathSize] = treeptr;
    search.pathSize = search.pathSize + 1;

    if (treeptr == nullptr)
    {
        treeptr = new (nothrow) TreeNode(newitem, nullptr, nullptr);
        search.path[search.pathSize - 1] = treeptr;
        if (treeptr == nullptr)
            throw Exception("No room in memory");
    }
    else if (newitem == treeptr->item)
    {
        throw Exception("Phone number already exists in the dictionary");
    }
    else if (newitem < treeptr->item)
    {
        BSTinsertAndMakeSearchPath(newitem, treeptr->leftChild, search);
    }
    else
    {
        BSTinsertAndMakeSearchPath(newitem, treeptr->rightChild, search);
    }
}

//Hunter Congress, Dylan Hay, Ryan Schoenlein, and Dr. Y

//checks to see if the search path has a pivot
//pre: AVL tree exists search's path has been
//     set to the nodes in the tree that formed the search path
//     also, search's pathSize >= 1
// post: if there is a pivot, then sets search's pivotIndex
//       so that search.path[search.pivotIndex]
//       points to the pivot node and returns false
//		 it will return true
// usage: if (hasNoPivot(search))
bool hasNoPivot(SearchPath &search)
{
    const int TOP = 0;
    for (int k = search.pathSize - 1; k >= TOP; k--)
    {
        if (search.path[k]->balance != 0)
        {
            search.pivotIndex = k;
            return false;
        }
    }
    return true;
}

// Authors: Maxwell Chehab, Michael Fontanilla, Michael Newell

// Changes the balances along the provided search path
// from start to the parent of the inserted node.
// pre search has to exist, start is greater than or equal to 0.
// post the balances of the search path are incremented or decremented
// depending if they have a left or right child.
// usage fixBalances(search, 0);
void fixBalances(const SearchPath &search, int start)
{
    for (int k = start; k < search.pathSize; k++)
    {
        if (search.path[k + 1] != nullptr and search.path[k]->leftChild == search.path[k + 1])
        {
            search.path[k]->balance -= 1;
        }
        else if (search.path[k + 1] != nullptr and search.path[k]->rightChild == search.path[k + 1])
        {
            search.path[k]->balance += 1;
        }
    }
}

// group members: Drew Bies, Andrew Flagstead,
//                Kevin Mattappally, Bo Volwiler, Dr. Y

// checks to see if a node
// was added to the "short side",the side with the
// lesser height
// pre: search's path has been assigned to the nodes in the tree
//      of the search path with nonzero pathSize.
//      it has been determined that there is
//      a pivot along the path so search.pivotIndex >= 0
// post: returns whether or not the node was
//       added to the short side
// usage: if(isAddedToShortSide(theSearchPath))
bool isAddedToShortSide(const SearchPath &search)
{
    // if the right side is the tall side
    if (search.path[search.pivotIndex]->balance == 1)
    {
        // check to see if the path goes to the short side (to the left)
        return (search.path[search.pivotIndex + 1] == search.path[search.pivotIndex]->leftChild);
    }
    // if the left side is the tall side
    else // if (search.path[search.pivotIndex] -> balance == -1)
    {
        // check to see if the path goes to the short side (to the right)
        return (search.path[search.pivotIndex + 1] == search.path[search.pivotIndex]->rightChild);
    }
}

//By Christian Kruep, Davis Fairchild, Sam Atkinson, Dr. Y

//Checks the search path of an AVLTree to see if the search path goes right
//	from the pivot node twice.
//PRE: search has been assigned: it has been determined that there is a pivot
//     so search.pivotIndex >= 0. search.pathSize > 0 and large enough to
//     have search.pivotIndex + 2 to have a non-nullptr.
//POST: returns true if the search path goes right from the pivot twice.
//		else returns false.
//USAGE: if(isSingleRotateLeft(search)
bool isSingleRotateLeft(const SearchPath &search)
{
    int pivot = search.pivotIndex;

    if (search.path[pivot]->rightChild != nullptr && search.path[pivot]->rightChild == search.path[pivot + 1])
    {
        return (search.path[pivot + 1]->rightChild != nullptr and
                search.path[pivot + 1]->rightChild == search.path[pivot + 2]);
    }
    return false;
}

// Brett Barinaga, Alli Fellger, Amy Larson

// Determines whether or not there is the necessity of a single right
// rotation in order to restore balance in an AVL tree.

// pre:    - search is assigned and filled with pointers to each node in the order that they were
//           traversed to place the new Item.
//         - pivotIndex is assigned the index value for the pointer in search that is directed at the first
//           unbalanced node along the search path starting with the newly inserted Item.
// 	       - pathsize is large enough to have a search.pivotIndex + 2
// post: returns true if search indicates that the pivot is followed by two left paths, and false otherwise.
// usage: if(isSingleRightRotate(aPath)) { doSingleRightRotate(); }
bool isSingleRotateRight(const SearchPath &search)
{
    if (search.path[search.pivotIndex]->leftChild != nullptr and
        search.path[search.pivotIndex]->leftChild == search.path[search.pivotIndex + 1])
    {
        return (search.path[search.pivotIndex + 1]->leftChild != nullptr and
                search.path[search.pivotIndex + 1]->leftChild == search.path[search.pivotIndex + 2]);
    }
    return false;
}

//authors: Andrew Abbott, John Distinti, Michael Hepburn, Kevin Shaw, Dr. Y

// tells whether or not the tree will need a double left right rotation
//pre: search exists, search.pivotIndex must be assigned to a non-negative number
//			search.path[search.pivotIndex}is assigned to the pivot
//     search.pathSize is large enough so search.path[search.pivotIndex + 2] is not
//     the nullptr
//post: returns true if search path goes left from the pivot and then right
//			Otherwise, is false
//usage: if (isDoubleRotateLeftRight(search))
bool isDoubleRotateLeftRight(const SearchPath &search)
{
    bool isRotation = false;
    int pivot = search.pivotIndex;

    if (search.path[pivot]->leftChild == search.path[pivot + 1])
    {
        if (search.path[pivot + 1] != nullptr &&
            search.path[pivot + 1]->rightChild == search.path[pivot + 2])
        {
            isRotation = true;
        }
    }
    return isRotation;
}

AVLTree::AVLTree()
{
}

AVLTree::~AVLTree()
{
}

TreeNode *doLeftRotate(SearchPath &search)
{
    TreeNode *cloud = search.path[search.pivotIndex - 1];
    TreeNode *pivot = search.path[search.pivotIndex];
    TreeNode *pivotChild = search.path[search.pivotIndex + 1];
    TreeNode *T1 = pivot->leftChild;
    TreeNode *T2 = pivotChild->leftChild;
    TreeNode *T3 = pivotChild->rightChild;

    pivotChild->rightChild = T3;
    pivotChild->leftChild = pivot;
    pivot->leftChild = T1;
    pivot->rightChild = T2;

    if (search.pivotIndex == 0)
    {
        TreeNode *tempNode = pivotChild;
        search.path[0] = tempNode;
    }
    else if (cloud->rightChild == pivot)
    {
        cloud->rightChild = pivotChild;
    }
    else
    {
        cloud->leftChild = pivotChild;
    }

    pivotChild->balance = 0;
    pivot->balance = 0;

    return search.path[0];
}

TreeNode *doRightRotate(SearchPath &search)
{
    TreeNode *cloud = search.path[search.pivotIndex - 1];
    TreeNode *pivot = search.path[search.pivotIndex];
    TreeNode *pivotChild = search.path[search.pivotIndex + 1];
    TreeNode *T1 = pivot->rightChild;
    TreeNode *T2 = pivotChild->rightChild;
    TreeNode *T3 = pivotChild->leftChild;

    pivotChild->leftChild = T3;
    pivotChild->rightChild = pivot;
    pivot->rightChild = T1;
    pivot->leftChild = T2;

    if (search.pivotIndex == 0)
    {
        TreeNode *tempNode = pivotChild;
        search.path[0] = tempNode;
    }
    else if (cloud->rightChild == pivot)
    {
        cloud->rightChild = pivotChild;
    }
    else
    {
        cloud->leftChild = pivotChild;
    }

    pivotChild->balance = 0;
    pivot->balance = 0;

    return search.path[0];
}

TreeNode *doDoubleRotateLeftRight(SearchPath &search)
{
    TreeNode *cloud = search.path[search.pivotIndex - 1];
    TreeNode *pivot = search.path[search.pivotIndex];
    TreeNode *pivotChild = search.path[search.pivotIndex + 1];
    TreeNode *grandChild = search.path[search.pivotIndex + 2];
    TreeNode *T1 = pivotChild->leftChild;
    TreeNode *T2 = grandChild->leftChild;
    TreeNode *T3 = grandChild->rightChild;
    TreeNode *T4 = pivot->rightChild;

    bool leftChild = search.path[search.pathSize - 2]->leftChild == search.path[search.pathSize - 1];

    grandChild->leftChild = pivotChild;
    grandChild->rightChild = pivot;
    pivotChild->leftChild = T1;
    pivotChild->rightChild = T2;
    pivot->leftChild = T3;
    pivot->rightChild = T4;
    grandChild->balance = 0;

    if (search.pivotIndex == 0)
    {
        TreeNode *tempNode = grandChild;
        search.path[0] = tempNode;
    }
    else if (cloud->rightChild == pivot)
    {
        cloud->rightChild = grandChild;
    }
    else
    {
        cloud->leftChild = grandChild;
    }

    if (leftChild)
    {
        pivot->balance = 1;
        pivotChild->balance = 0;
    }
    else
    {
        pivot->balance = 0;
        pivotChild->balance = 1;
    }
    search.path[search.pathSize - 2]->balance = 0;

    return search.path[0];
}

TreeNode *doDoubleRotateRightLeft(SearchPath &search)
{
    TreeNode *cloud = search.path[search.pivotIndex - 1];
    TreeNode *pivot = search.path[search.pivotIndex];
    TreeNode *pivotChild = search.path[search.pivotIndex + 1];
    TreeNode *grandChild = search.path[search.pivotIndex + 2];
    TreeNode *T1 = pivotChild->rightChild;
    TreeNode *T2 = grandChild->rightChild;
    TreeNode *T3 = grandChild->leftChild;
    TreeNode *T4 = pivot->leftChild;

    bool leftChild = search.path[search.pathSize - 2]->leftChild == search.path[search.pathSize - 1];

    grandChild->rightChild = pivotChild;
    grandChild->leftChild = pivot;
    pivotChild->rightChild = T1;
    pivotChild->leftChild = T2;
    pivot->rightChild = T3;
    pivot->leftChild = T4;
    grandChild->balance = 0;

    if (search.pivotIndex == 0)
    {
        TreeNode *tempNode = grandChild;
        search.path[0] = tempNode;
    }
    else if (cloud->rightChild == pivot)
    {
        cout << "RIGHT" << endl;
        cloud->rightChild = grandChild;
    }
    else
    {
        cout << "LEFT" << endl;
        cloud->leftChild = grandChild;
    }

    if (leftChild)
    {
        cout << "left child" << endl;
        pivot->balance = 0;
        pivotChild->balance = 1;
    }
    else
    {
        cout << "right child" << endl;
        pivot->balance = 1;
        pivotChild->balance = 0;
    }
    search.path[search.pathSize - 2]->balance = 0;

    return search.path[0];
}

void AVLTree::insert(const Item &newItem) throw(Exception)
{
    SearchPath search;
    BSTinsertAndMakeSearchPath(newItem, root, search);

    if (hasNoPivot(search))
    {
        fixBalances(search, 0);
    }
    else if (isAddedToShortSide(search))
    {
        fixBalances(search, search.pivotIndex);
    }
    else if (isSingleRotateLeft(search))
    {
        root = doLeftRotate(search);
        fixBalances(search, search.pivotIndex + 2);
    }
    else if (isSingleRotateRight(search))
    {
        root = doRightRotate(search);
        fixBalances(search, search.pivotIndex + 2);
    }

    else if (isDoubleRotateLeftRight(search))
    {
        cout << 4 << endl;
        root = doDoubleRotateLeftRight(search);
        fixBalances(search, search.pivotIndex + 3);
    }
    else
    {
        cout << 5 << endl;

        root = doDoubleRotateRightLeft(search);
        fixBalances(search, search.pivotIndex + 3);
        //   perhaps a call to fixBalances
    }
}