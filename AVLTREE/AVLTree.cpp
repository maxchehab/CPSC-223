#include "AVLTree.h"

const int MAXHEIGHT = 10;

struct SearchPath 
{
    TreeNode* path [MAXHEIGHT];
    int pathSize;
    int pivotIndex;
    SearchPath();
};

SearchPath::SearchPath()
{
    pathSize = 0;
    pivotIndex = 0;
    for(int k = 0; k < MAXHEIGHT; k++) {
        path[k] = nullptr;
    }
}

void fixBalances(const SearchPath& search, int start) {
	for(int k = start; k < MAXHEIGHT; k++) {
		if(search.path[k + 1] == nullptr) {
			break;
		} else if(search.path[k]->leftChild == search.path[k + 1]){
			search.path[k]->balance -= 1;
		} else if(search.path[k]->rightChild == search.path[k + 1]){
			search.path[k]->balance += 1;
		}
	}
}

AVLTree::AVLTree() 
{

}

AVLTree::~AVLTree()
{

}

void AVLTree::insert(const Item& newItem) throw (Exception) 
{

}
