CC = /usr/bin/g++
FLAGS = -g -I../include
LIBS = -L/usr/local/lib -rdynamic -lplayerc++ -lboost_thread -lboost_system -lboost_signals -lplayerc -lm -lz -lplayerinterface -lplayerwkb -lplayercommon -Wl,-rpath,/usr/local/lib
BIN = bin
PROJECT_BIN = ../bin
OBJ = $(BIN)/png.o $(BIN)/coordinate.o $(BIN)/utils.o

test: testMap.cpp map.cpp $(OBJ)
	$(CC) $(FLAGS) -o $(BIN)/$@ $^

map.o: map.cpp
	$(CC) $(FLAGS) $(LIBS) -c $^ -o $(PROJECT_BIN)/$@

$(BIN)/coordinate.o: $(PROJECT_BIN)/coordinate.o
	cp $^ $@

$(BIN)/utils.o: $(PROJECT_BIN)/utils.o
	cp $^ $@

$(BIN)/png.o: $(PROJECT_BIN)/lodepng.o
	cp $^ $@

.PHONY: clean
clean:
	rm $(BIN)/*



