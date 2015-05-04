CC = /usr/bin/g++
FLAGS = -g -I../include -I/usr/local/include/player-3.1
LIBS = -L/usr/local/lib -rdynamic -lplayerc++ -lboost_thread -lboost_system -lboost_signals -lplayerc -lm -lz -lplayerinterface -lplayerwkb -lplayercommon -Wl,-rpath,/usr/local/lib
BIN = bin
PROJECT_BIN = ../bin
OBJ = $(BIN)/map.o $(BIN)/coordinate.o $(BIN)/png.o $(BIN)/utils.o $(BIN)/stack.o

test: testNav.cpp navigator.cpp $(OBJ)
	$(CC) $(FLAGS) -o $(BIN)/$@ $^

navigator.o: navigator.cpp
	$(CC) $(FLAGS) $(LIBS) -c $^ -o $(PROJECT_BIN)/$@

$(BIN)/png.o: $(PROJECT_BIN)/lodepng.o
	cp $^ $@

$(BIN)/map.o: $(PROJECT_BIN)/map.o
	cp $^ $@

$(BIN)/coordinate.o: $(PROJECT_BIN)/coordinate.o
	cp $^ $@

$(BIN)/utils.o: $(PROJECT_BIN)/utils.o
	cp $^ $@

$(BIN)/stack.o: $(PROJECT_BIN)/stack.o
	cp $^ $@

.PHONY: clean
clean:
	rm $(BIN)/*



