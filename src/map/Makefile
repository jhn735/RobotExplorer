CC = /usr/bin/g++
FLAGS = -g -I../include
BIN = bin
PROJECT_BIN = ../bin
OBJ = $(BIN)/png.o $(BIN)/coordinate.o $(BIN)/utils.o

test: testMap.cpp map.cpp $(OBJ)
	$(CC) $(FLAGS) -o $(BIN)/$@ $^

map.o: map.cpp
	$(CC) $(FLAGS) -c $^ -o $(PROJECT_BIN)/$@

$(BIN)/coordinate.o: $(PROJECT_BIN)/coordinate.o
	cp $^ $@

$(BIN)/utils.o: $(PROJECT_BIN)/utils.o
	cp $^ $@

$(BIN)/png.o: $(PROJECT_BIN)/lodepng.o
	cp $^ $@

.PHONY: clean
clean:
	rm $(BIN)/*



