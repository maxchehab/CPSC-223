all: Dictionary.cpp Clientprogram.cpp Item.cpp Key.cpp 
	g++ -std=c++11 Stack.cpp Dictionary.cpp Clientprogram.cpp Item.cpp Key.cpp -o Gochain
	./Gochain

build: Hashprogram.cpp 	
	g++ -std=c++11 Stack.cpp Dictionary.cpp Clientprogram.cpp Item.cpp Key.cpp -o Gohash

clean: 
	$(RM) ./Gohash

run: Gohash
	./Gohash
