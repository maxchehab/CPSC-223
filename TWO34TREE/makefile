all: Exception.cpp Clientprogram.cpp Two34TreeNode.cpp Two34Tree.cpp  Item.cpp Key.cpp
	clang++ -std=c++11 Exception.cpp Clientprogram.cpp Two34TreeNode.cpp Two34Tree.cpp Item.cpp Key.cpp -o gotree 
	# -Wno-tautological-pointer-compare 
	./gotree

clean: 
	$(RM) ./gotree

run: gotree
	./gotree

