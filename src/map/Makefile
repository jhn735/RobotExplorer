CC = /usr/bin/g++
FLAGS = -g -I../include
BIN = bin
PROJECT_BIN = ../bin

test: testMap.cpp map.cpp $(BIN)/png.o $(BIN)/coordinate.o
	$(CC) $(FLAGS) -o $(BIN)/$@ $^

map.o: map.cpp
	$(CC) $(FLAGS) -c $^ -o $(PROJECT_BIN)/$@

$(BIN)/coordinate.o: $(PROJECT_BIN)/coordinate.o
	cp $^ $@

$(BIN)/png.o: $(PROJECT_BIN)/lodepng.o
	cp $^ $@

.PHONY: clean
clean:
	rm $(BIN)/*



