CC = /usr/bin/g++
FLAGS = -g -I../include
BIN = bin
PROJECT_BIN = ../bin

test: testNav.cpp navigator.cpp $(BIN)/map.o $(BIN)/coordinate.o
	$(CC) $(FLAGS) -o $(BIN)/$@ $^

navigator.o: navigator.cpp
	$(CC) $(FLAGS) -c $^ -o $(PROJECT_BIN)/$@

$(BIN)/map.o: $(PROJECT_BIN)/map.o
	cp $^ $@

$(BIN)/coordinate.o: $(PROJECT_BIN)/coordinate.o
	cp $^ $@

.PHONY: clean
clean:
	rm $(BIN)/*



