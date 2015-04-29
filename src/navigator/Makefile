CC = /usr/bin/g++
FLAGS = -g -I../include
BIN = bin
PROJECT_BIN = ../bin
OBJ = $(BIN)/map.o $(BIN)/coordinate.o $(BIN)/png.o $(BIN)/utils.o

test: testNav.cpp navigator.cpp $(OBJ)
	$(CC) $(FLAGS) -o $(BIN)/$@ $^

navigator.o: navigator.cpp
	$(CC) $(FLAGS) -c $^ -o $(PROJECT_BIN)/$@

$(BIN)/png.o: $(PROJECT_BIN)/lodepng.o
	cp $^ $@

$(BIN)/map.o: $(PROJECT_BIN)/map.o
	cp $^ $@

$(BIN)/coordinate.o: $(PROJECT_BIN)/coordinate.o
	cp $^ $@

$(BIN)/utils.o: $(PROJECT_BIN)/utils.o
	cp $^ $@
.PHONY: clean
clean:
	rm $(BIN)/*



