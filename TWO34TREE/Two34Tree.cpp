// Specification of ADT 2-3-4 Tree
//     data object: a 2-3-4 tree (a tree containing 2-nodes,
//                  3-nodes, and 4-nodes) where a k-node has
//                  k children
// note: this is not the formal definition that takes 2 pages in textbook
//     operations: create, destroy, insert, display
// Programmer: dr y     Date: April 16, 2002
// Filename: Two34Tree.h
//
// class Two34TreeNode specifies and implements a node for a
//    2-3-4 tree with room for 1-3 data items from class citem and
//    0-4 children

#include "Two34Tree.h"

using namespace std;

// frees the heap memory of a tree
// pre: treep is assigned but may be empty
// post: all nodes in the tree with root treep
//       have been released back to the heap and
//       treep is empty
// usage: destroyTree (mroot);
void destroyTree(Two34TreeNode *&treep)
{
    if (treep != nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            destroyTree(treep->kids[i]);
        }
        delete treep;
        treep = nullptr;
    }
}

// shows the data in the tree in inorder
// pre: treep is assigned but may be empty
//      output is open
// post: the data items in the nodes of treep's tree
//       are printed to output in inorder
void inorder(ostream &output, Two34TreeNode *treep)
{
    if (treep != nullptr)
    {
        inorder(output, treep->kids[0]);
        inorder(output, treep->kids[1]);
        for (int i = 0; i < 3; i++)
        {
            output << treep->kids[i] << " ";
        }
        inorder(output, treep->kids[2]);
        inorder(output, treep->kids[3]);
    }
}

// shows the data in the tree in its tree structure
// pre: output is open. treep is assigned a tree.
//      level is assigned
// post: the data items of the nodes of treep at level
//       in the tree are printed to output with spacing
//       to denote the level.
// usage: pretty (output, mroot, 1);
void pretty(ostream &output, Two34TreeNode *treep, int level)
{
    Key emptyKey;
    emptyKey.emptyIt();
    if (treep != nullptr)
    {
        for (int i = 0; i < level; i++)
        {
            output << "\t";
        }
        output << "[ ";
        for (int i = 0; i < 3; i++)
        {
            if (!(treep->keys[i] == emptyKey))
            {
                output << treep->keys[i] << " ";
            }
        }
        output << "]" << endl;
        for (int i = 3; i >= 0; i--)
        {
            pretty(output, treep->kids[i], level + 1);
        }
    }
}

bool treeNodeHasSpace(const Two34TreeNode *treep, int &index)
{
    Key emptyKey;
    emptyKey.emptyIt();

    for (int i = 0; i < 3; i++)
    {
        if (treep->keys[i] == emptyKey)
        {
            index = i;
            return true;
        }
    }
    return false;
}

void pushNegativeKeysToEnd(Two34TreeNode *treep)
{
    Key emptyKey;
    emptyKey.emptyIt();

    int count = 0;

    for (int i = 0; i < 3; i++)
        if (!(treep->keys[i] == emptyKey))
            treep->keys[count++] = treep->keys[i];

    while (count < 3)
        treep->keys[count++] = emptyKey;
}

void sortTreeNode(Two34TreeNode *treep)
{
    Key emptyKey;
    emptyKey.emptyIt();
    for (int i = 1; i < 3; i++)
    {
        Key index = treep->keys[i];
        int j = i;
        while (j > 0 && index < treep->keys[j - 1])
        {
            treep->keys[j] = treep->keys[j - 1];
            j--;
        }
        treep->keys[j] = index;
    }
    pushNegativeKeysToEnd(treep);
}

bool getIndexOfItem(const Two34TreeNode *treep, const Key newKey, int newItemIndex)
{
    for (int newItemIndex = 0; newItemIndex < 3; newItemIndex++)
    {
        if (treep->keys[newItemIndex] == newKey)
        {
            return true;
        }
    }
    return false;
}

void addOrCreateKid(Two34TreeNode **treep, Two34TreeNode *left, Two34TreeNode *right, const int index, const Key newKey)
{
    int freeIndex = 0;
    int newItemIndex = 0;

    if ((*treep)->kids[index] == nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            if ((*treep)->kids[i] == nullptr)
            {
                cout << "-1 ";
            }
            else
            {
                cout << (*treep)->kids[i]->keys[0] << " ";
            }
        }
        cout << endl;
        cout << "there is no tree node at " << index << " " << (*treep)->keys[0] << endl;
        (*treep)->kids[index] = new Two34TreeNode(newKey, left, right);
        for (int i = 0; i < 4; i++)
        {
            if ((*treep)->kids[i] == nullptr)
            {
                cout << "-1 ";
            }
            else
            {
                cout << (*treep)->kids[i]->keys[0] << " ";
            }
        }
        cout << endl;
    }
    else if (treeNodeHasSpace((*treep)->kids[index], freeIndex))
    {
        (*treep)->kids[index]->keys[freeIndex] = newKey;

        sortTreeNode((*treep)->kids[index]);
        if (getIndexOfItem((*treep), newKey, newItemIndex)) // TODO instead of replace, add
        {
            cout << "adding " << left->keys[0] << endl;
            cout << "adding " << right->keys[0] << endl;
            (*treep)->kids[newItemIndex] = left;
            (*treep)->kids[newItemIndex + 1] = right;
        }
        else
        {
            cout << "something else has gone wrong :: addOrCreateKid" << endl;
        }
    }
    else
    {
        cout << "something has gone wrong :: addOrCreateKid" << endl;
    }
}

void findIndexForKid(Two34TreeNode *treep, const Key newKey, int &index)
{
    for (index = 0; index < 3; index++)
    {
        if ((newKey < treep->keys[index]))
        {
            break;
        }
    }
}

void splitTreeNode(Two34TreeNode **target, Two34TreeNode **parent, bool &changeTarget)
{

    int freeIndex = 0;
    int newIndex = 0;

    if (*parent == nullptr)
    {
        cout << "splitTreeNode:: parent is a nullptr (root)" << endl;
        Two34TreeNode *left = (*target)->kids[0];
        Two34TreeNode *middleLeft = (*target)->kids[1];
        Two34TreeNode *middleRight = (*target)->kids[2];
        Two34TreeNode *right = (*target)->kids[3];

        if (left != nullptr)
            cout << "left: " << left->keys[0] << endl;
        if (middleLeft != nullptr)
            cout << "middleLeft: " << middleLeft->keys[0] << endl;
        if (middleRight != nullptr)
            cout << "middleRight: " << middleRight->keys[0] << endl;
        if (right != nullptr)
            cout << "right: " << right->keys[0] << endl;

        (*target)->kids[0] = new Two34TreeNode((*target)->keys[0], left, middleLeft);
        (*target)->kids[3] = new Two34TreeNode((*target)->keys[2], middleRight, right);

        (*target)->kids[1] = nullptr;
        (*target)->kids[2] = nullptr;

        cout << "middle left is nullptr :: " << (middleLeft == nullptr) << endl;

        (*target)->keys[0].emptyIt();
        (*target)->keys[2].emptyIt();
        sortTreeNode(*target);
        changeTarget = true;
    }
    else
    {
        cout << "splitTreeNode:: parent is not a nullptr: " << (*parent)->keys[0] << endl;
        if (treeNodeHasSpace(*parent, freeIndex))
        {
            (*parent)->keys[freeIndex] = (*target)->keys[1];
            sortTreeNode(*parent);

            Two34TreeNode *left = (*target)->kids[0];
            Two34TreeNode *middleLeft = (*target)->kids[1];
            Two34TreeNode *middleRight = (*target)->kids[2];
            Two34TreeNode *right = (*target)->kids[3];

            if (left != nullptr)
                cout << "left: " << left->keys[0] << endl;
            if (middleLeft != nullptr)
                cout << "middleLeft: " << middleLeft->keys[0] << endl;
            if (middleRight != nullptr)
                cout << "middleRight: " << middleRight->keys[0] << endl;
            if (right != nullptr)
                cout << "right: " << right->keys[0] << endl;

            Key leftChild = (*target)->keys[0];
            Key rightChild = (*target)->keys[2];

            // delete *target;
            *target = nullptr;

            findIndexForKid(*parent, leftChild, newIndex);
            addOrCreateKid(parent, middleLeft, left, newIndex, leftChild);

            findIndexForKid(*parent, rightChild, newIndex);
            addOrCreateKid(parent, middleRight, right, newIndex, rightChild);

            changeTarget = false;
        }
        else
        {
            cout << "something terrible has happened: splitTreeNode" << endl;
        }
    }
}

bool treeNodeHasNoKids(Two34TreeNode *treep)
{
    for (int i = 0; i < 4; i++)
    {
        if (treep->kids[i] != nullptr)
        {
            return false;
        }
    }
    return true;
}

// creates an empty 2-3-4 Tree
// post: object is empty
Two34Tree::Two34Tree()
{
    root = nullptr;
}

// destroys a 2-3-4 Tree
// pre: object exists
// post: object does not exist, all pre-memory released
Two34Tree::~Two34Tree()
{
    delete root;
    root = nullptr;
}

// inserts a new key into the tree
// pre: tree object exists. newKey is assigned.
// post: newKey is placed in the appropriately sorted
//       position in the 2-3-4 tree object
// usage: tree.insert(mykey);
void Two34Tree::insert(const Key &newKey)
{
    Key emptyKey;
    emptyKey.emptyIt();
    int freeIndex = 0;
    int nextIndex = 0;
    bool stop = false;
    bool swapTarget = true;
    Two34TreeNode *temp = nullptr;
    Two34TreeNode **parent = &temp;
    Two34TreeNode **target = &root;

    while (!stop)
    {
        cout << "parent is " << (*parent == nullptr ? emptyKey : (*parent)->keys[0]) << endl;
        cout << "target is " << (*target == nullptr ? emptyKey : (*target)->keys[0]) << endl;

        if (*parent == nullptr && *target == nullptr)
        {
            cout << "adding to root" << endl;
            (*target) = new Two34TreeNode(newKey);
            stop = true;
        }
        // else if (*parent == nullptr && ) //has no children
        else if (treeNodeHasNoKids(*target))
        {
            if (treeNodeHasSpace(*target, freeIndex))
            {
                cout << "node has no children and has space" << endl;
                (*target)->keys[freeIndex] = newKey;
                sortTreeNode(*target);
                stop = true;
            }
            else
            {

                cout << "node has no children but is full" << endl;
                splitTreeNode(target, parent, swapTarget);
                pretty(cout, root, 0);
                findIndexForKid(*target, newKey, nextIndex);
                cout << nextIndex << endl;
                if (swapTarget)
                {
                    parent = target;
                    target = &((*target)->kids[nextIndex]);
                }
            }
        }
        else if (!treeNodeHasSpace(*target, freeIndex))
        {
            cout << "node has no children but is full" << endl;
            splitTreeNode(target, parent, swapTarget);
            pretty(cout, root, 0);
            findIndexForKid(*target, newKey, nextIndex);
            cout << nextIndex << endl;
            if (swapTarget)
            {
                parent = target;
                target = &((*target)->kids[nextIndex]);
            }
        }
        else
        {
            cout << "traverse" << endl;
            findIndexForKid(*target, newKey, nextIndex);
            cout << nextIndex << endl;
            parent = target;
            target = &((*target)->kids[nextIndex]);
        }
    }
}

// displays a tree in one of two formats
// pre: which is either 'i' or 'p'
//      output is open
// post: if which is 'i' the tree is displayed inorder
//       else the tree is displayed showing its tree
//       structure
// usage: tree.display (cout, 'p');
void Two34Tree::display(ostream &output, char which)
{
    if (which == 'i')
    {
        inorder(output, root);
    }
    else
    {
        pretty(output, root, 0);
    }
}