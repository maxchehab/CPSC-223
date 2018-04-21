// fixBalances.cpp
// Authors: Maxwell Chehab, Michael Fontanilla, Michael Newell
// 04/06/18
// This program houses a fixBalances function which calculates the
// new balances for an ADT AVLTREE.

// Changes the balances along the provided search path 
// from start to the parent of the inserted node.
// pre search has to exist, start is greater than or equal to 0.
// post the balances of the search path are incremented or decremented 
// depending if they have a left or right child.
// usage fixBalances(search, 0);
void fixBalances(const SearchPath& search, int start) {
	for(int k = start; k < MAXHEIGHT; k++) {
		if(search.path[k + 1] != nullptr and search.path[k]->leftChild == search.path[k + 1]){
			search.path[k]->balance -= 1;
		} else if(search.path[k + 1] != nullptr and search.path[k]->rightChild == search.path[k + 1]){
			search.path[k]->balance += 1;
		}
	}
}

/*
We were unsure if this recursive version of fixBalances is allowed. 
But we would like to submit it along with the loop variant to show that
we thought of it.
void fixBalances(const SearchPath& search, int start) {
	if(search.path[start + 1] != nullptr) {
		if(search.path[start]->leftChild == search.path[start + 1]){
			search.path[start]->balance -= 1;
		} else if(search.path[start]->rightChild == search.path[start + 1]){
			search.path[start]->balance += 1;
		}
		fixBalance(search, start++);
	}
}
*/
