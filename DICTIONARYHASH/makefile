all: Dictionary.cpp Clientprogram.cpp Item.cpp Key.cpp 
	g++ Dictionary.cpp Clientprogram.cpp Item.cpp Key.cpp -o Gohash
	./Gohash

build: Hashprogram.cpp 	
	g++ Dictionary.cpp Clientprogram.cpp Item.cpp Key.cpp -o Gohash
clean: 
	$(RM) ./Gohash

run: Gohash
	./Gohash
