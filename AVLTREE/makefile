all: Exception.cpp Clientprogram.cpp TreeNode.cpp BinarySearchTree.cpp BinaryTree.cpp  Item.cpp Key.cpp
	clang++ -std=c++11 Exception.cpp Clientprogram.cpp TreeNode.cpp BinarySearchTree.cpp BinaryTree.cpp  Item.cpp Key.cpp -o Dodictionary 
	./Dodictionary

test: Exception.cpp Searchtreetester.cpp TreeNode.cpp BinarySearchTree.cpp BinaryTree.cpp  Item.cpp Key.cpp
	clang++ -std=c++11 Exception.cpp Searchtreetester.cpp TreeNode.cpp BinarySearchTree.cpp BinaryTree.cpp  Item.cpp Key.cpp -o Searchtreetester 
	./Searchtreetester


build: Exception.cpp Clientprogram.cpp TreeNode.cpp BinarySearchTree.cpp BinaryTree.cpp  Item.cpp Key.cpp
	clang++ -std=c++11 Exception.cpp Clientprogram.cpp TreeNode.cpp BinarySearchTree.cpp BinaryTree.cpp  Item.cpp Key.cpp -o Dodictionary
clean: 
	$(RM) ./Dodictionary
	$(RM) ./Searchtreetester

run: Dodictionary
	./Dodictionary

