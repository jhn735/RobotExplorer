CC = /usr/bin/g++
FLAGS = -g -I../include
BIN = bin

test:  testMap.cpp map.cpp map_utilities.cpp lodepng.cpp
	$(CC) $(FLAGS) -o $(BIN)/$@ $^

.PHONY: clean
clean:
	rm $(BIN)/*



