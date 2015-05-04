CC = /usr/bin/g++
FLAGS = -g -Wall -I/usr/local/include/player-3.1 -I./include
LIBS = -L/usr/local/lib -rdynamic -lplayerc++ -lboost_thread -lboost_system -lboost_signals -lplayerc -lm -lz -lplayerinterface -lplayerwkb -lplayercommon -Wl,-rpath,/usr/local/lib
PROJECT_BIN = bin

REQS = $(PROJECT_BIN)/robot.o $(PROJECT_BIN)/map.o $(PROJECT_BIN)/navigator.o\
$(PROJECT_BIN)/coordinate.o $(PROJECT_BIN)/stack.o $(PROJECT_BIN)/utils.o \
$(PROJECT_BIN)/lodepng.o

all: main.cpp $(REQS) 
	$(CC) $(FLAGS) $^ $(LIBS) -o $@

$(PROJECT_BIN)/robot.o: robot/robot.cpp
	$(CC) $(FLAGS) $(LIBS) -c $^ -o $@

$(PROJECT_BIN)/map.o: map/map.cpp
	$(CC) $(FLAGS) $(LIBS) -c $^ -o $@

$(PROJECT_BIN)/navigator.o: navigator/navigator.cpp
	$(CC) $(FLAGS) $(LIBS) -c $^ -o $@

$(PROJECT_BIN)/coordinate.o: utils/coordinate.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(PROJECT_BIN)/stack.o: utils/stack.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(PROJECT_BIN)/utils.o: utils/utils.cpp
	$(CC) $(FLAGS) -c $^ -o $@
	
$(PROJECT_BIN)/lodepng.o:  lodepng/lodepng.cpp
	$(CC) $(FLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm $(PROJECT_BIN)/*.o

