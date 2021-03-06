// Specification of ADT 2-3-4 Tree
//     data object: a 2-3-4 tree (a tree containing 2-nodes,
//                  3-nodes, and 4-nodes) where a k-node has
//                  k children
// note: this is not the formal definition that takes 2 pages in textbook
//     operations: createkz, destroy, insert, display
// Programmer: Max Chehab    Date: April 17, 2018
// Filename: Two34Tree.cpp
//
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
    if (treep != nullptr)
    {
        pretty(output, treep->kids[3], level + 1);
        pretty(output, treep->kids[2], level + 1);
		for (int i = 0; i < level; i++)
		{
			output << "\t";
		}
		output << "[ ";
        for (int i = 0; i < 3; i++)
        {
            if (!(treep->keys[i].isEmpty()))
            {
                output << treep->keys[i] << " ";
            }
        }
        output << "]" << endl;
        pretty(output, treep->kids[1], level + 1);
        pretty(output, treep->kids[0], level + 1);
		if (treep->kids[0] != nullptr)
		{
			output << endl;
		}
    }
}

// determines if a tree node contains a key.
//      useful for detecting duplicates.
// pre: tree node is not nullptr, key is not empty
// post: if the tree node contains a key true will return
//      else false
// usage: if (treeNodeContainsKey(target, newKey)) {cout << "duplicate";}
bool treeNodeContainsKey(const Two34TreeNode *treep, const Key &key)
{
    for (int i = 0; i < 3; i++)
    {
        if (treep->keys[i] == key)
        {
            return true;
        }
    }
    return false;
}

// determines if a tree node is full
// pre: tree node is not nullptr
// post: if all of a treenode's keys are occupied true will return
//      else false
// usage: if (treeNodeIsFull(target)) {cout << "need to split";}
bool treeNodeIsFull(const Two34TreeNode *treep)
{
    Key emptyKey;
    emptyKey.emptyIt();

    for (int i = 0; i < 3; i++)
    {
        if (treep->keys[i] == emptyKey)
        {
            return false;
        }
    }
    return true;
}

// determines if a tree node is a leaf
// pre: tree node is not nullptr
// post: if the tree node has no children true will return
//      else false
// usage: if (treeNodeIsLeaf(target)) {cout << "insert!";}
bool treeNodeIsLeaf(const Two34TreeNode *treep)
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

// determines what type a tree node is, either 1 node, 2 node or 3 node
// pre: tree node is not nullptr
// post: if the child has 1 key, 1 will be returned
//      2; 2 will be returned
//      3; 3 will be returned
// usage: if (treeNodeType(target) == 1) {cout << "is a 1 node!";}
int treeNodeType(Two34TreeNode *treep)
{
    for (int i = 2; i >= 0; i--)
    {
        if (!treep->keys[i].isEmpty())
        {
            return i + 1;
        }
    }

    return 0;
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
void Two34Tree::insert(const Key &newKey) throw(Exception)
{
    Two34TreeNode *target, *parent;
    int nodeType = 0;

    if (root == nullptr)
    {
        root = new (nothrow) Two34TreeNode(newKey);
        if (root == nullptr)
        {
            throw Exception("Insert :: no room in the heap");
        }
    }
    else
    {
        target = root;
        parent = target;

        while (target != nullptr)
        {
            if (treeNodeContainsKey(target, newKey))
            {
                throw Exception("Insert :: no duplicates");
            }
            else if (treeNodeIsFull(target))
            {
               // cout << "treeNodeIsFull" << endl;
                nodeType = treeNodeType(parent);
                //Parent is 1 node;
                if (nodeType == 1)
                {
                   // cout << "parent is 1 node" << endl;
                    if (parent->keys[0] < target->keys[1])
                    {
                        parent->keys[1] = target->keys[1];
                        parent->kids[1] = new (nothrow) Two34TreeNode(target->keys[0], target->kids[0], target->kids[1]);
                        if (parent->kids[1] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                        parent->kids[2] = new (nothrow) Two34TreeNode(target->keys[2], target->kids[2], target->kids[3]);
                        if (parent->kids[2] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                    }
                    else
                    {
                        parent->keys[1] = parent->keys[0];
                        parent->kids[2] = parent->kids[1];
                        parent->keys[0] = target->keys[1];
                        parent->kids[0] = new (nothrow) Two34TreeNode(target->keys[0], target->kids[0], target->kids[1]);
                        if (parent->kids[0] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                        parent->kids[1] = new (nothrow) Two34TreeNode(target->keys[2], target->kids[2], target->kids[3]);
                        if (parent->kids[1] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                    }

                    if (newKey < parent->keys[0])
                    {
                        target = parent->kids[0];
                    }
                    else if (newKey < parent->keys[1])
                    {
                        target = parent->kids[1];
                    }
                    else if (parent->keys[1] < newKey)
                    {
                        target = parent->kids[2];
                    }
                    else
                    {
                        throw Exception("Insert :: no duplicates");
                    }
                }
                else if (nodeType == 2)
                {
                   // cout << "parent is 2 node" << endl;

                    if (parent->keys[1] < target->keys[1])
                    {
                        parent->keys[2] = target->keys[1];
                        parent->kids[2] = new (nothrow) Two34TreeNode(target->keys[0], target->kids[0], target->kids[1]);
                        if (parent->kids[2] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                        parent->kids[3] = new (nothrow) Two34TreeNode(target->keys[2], target->kids[2], target->kids[3]);
                        if (parent->kids[3] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                    }
                    else if (parent->keys[0] < target->keys[1])
                    {
                        parent->keys[2] = parent->keys[1];
                        parent->kids[3] = parent->kids[2];
                        parent->keys[1] = target->keys[1];
                        parent->kids[1] = new (nothrow) Two34TreeNode(target->keys[0], target->kids[0], target->kids[1]);
                        if (parent->kids[1] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                        parent->kids[2] = new (nothrow) Two34TreeNode(target->keys[2], target->kids[2], target->kids[3]);
                        if (parent->kids[2] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                    }
                    else
                    {
                        parent->keys[2] = parent->keys[1];
                        parent->kids[3] = parent->kids[2];
                        parent->keys[1] = parent->keys[0];
                        parent->kids[2] = parent->kids[1];
                        parent->keys[0] = target->keys[1];
                        parent->kids[0] = new (nothrow) Two34TreeNode(target->keys[0], target->kids[0], target->kids[1]);
                        if (parent->kids[0] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                        parent->kids[1] = new (nothrow) Two34TreeNode(target->keys[2], target->kids[2], target->kids[3]);
                        if (parent->kids[1] == nullptr)
                        {
                            throw Exception("Insert :: no room in the heap");
                        }
                    }

                    if (newKey < parent->keys[0])
                    {
                        target = parent->kids[0];
                    }
                    else if (newKey < parent->keys[1])
                    {
                        target = parent->kids[1];
                    }
                    else if (newKey < parent->keys[2])
                    {
                        target = parent->kids[2];
                    }
                    else if (parent->keys[2] < newKey)
                    {
                        target = parent->kids[3];
                    }
                    else
                    {
                        throw Exception("Insert :: no duplicates");
                    }
                }
                else //if root and parent are three, talking about same node therefore influence just the root
                {
                   // cout << "parent is 3 node" << endl;

                    root = new Two34TreeNode(target->keys[1]);
                    if (root == nullptr)
                    {
                        throw Exception("Insert :: no room in the heap");
                    }
                    root->kids[0] = new (nothrow) Two34TreeNode(target->keys[0], target->kids[0], target->kids[1]);
                    if (root->kids[0] == nullptr)
                    {
                        throw Exception("Insert :: no room in the heap");
                    }
                    root->kids[1] = new (nothrow) Two34TreeNode(target->keys[2], target->kids[2], target->kids[3]);
                    if (root->kids[1] == nullptr)
                    {
                        throw Exception("Insert :: no room in the heap");
                    }

                    parent = root;

                    if (newKey < root->keys[0])
                    {
                        target = root->kids[0];
                    }
                    else if (root->keys[0] < newKey)
                    {
                        target = root->kids[1];
                    }
                    else
                    {
                        throw Exception("Insert :: no duplicates");
                    }
                }
              //  pretty(cout, root, 0);
            }

            if (treeNodeIsLeaf(target))
            {
                //cout << "is a leaf" << endl;
                nodeType = treeNodeType(target);

                if (nodeType == 1)
                {
					//cout << "node is one node" << endl;
                    if (target->keys[0] < newKey)
                    {
                        target->keys[1] = newKey;
                        return;
                    }
                    else if (newKey < target->keys[0])
                    {
                        target->keys[1] = target->keys[0];
                        target->keys[0] = newKey;
                        return;
                    }
                }
                else if (nodeType == 2)
                {
					//cout << "node is two node" << endl;
                    if (target->keys[1] < newKey)
                    {
						//cout << "placing in index 2" << endl;
                        target->keys[2] = newKey;
                        return;
                    }
                    else if (target->keys[0] < newKey)
                    {
						target->keys[2] = target->keys[1];
                        target->keys[1] = newKey;
						return;
					}
                    else if (newKey < target->keys[0])
                    {
						//cout << "placing in index 0" << endl;
                        target->keys[2] = target->keys[1];
                        target->keys[1] = target->keys[0];
                        target->keys[0] = newKey;
						return;
                    }
                }
            }
            else
            {
               // cout << "not a leaf" << endl;
                nodeType = treeNodeType(target);

                parent = target;

                if (nodeType == 1)
                {
                    if (newKey < target->keys[0])
                    {
                        target = target->kids[0];
                    }
                    else
                    {
                        target = target->kids[1];
                    }
                }
                else if (nodeType == 2)
                {
                    if (newKey < target->keys[0])
                    {
                        target = target->kids[0];
                    }
                    else if (newKey < target->keys[1])
                    {
                        target = target->kids[1];
                    }
                    else
                    {
                        target = target->kids[2];
                    }
                }
            }
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