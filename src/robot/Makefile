CC = /usr/bin/g++
FLAGS = -g -Wall -I/usr/local/include/player-3.1 -I../include 
LIBS = -L/usr/local/lib -rdynamic -lplayerc++ -lboost_thread -lboost_system -lboost_signals -lplayerc -lm -lz -lplayerinterface -lplayerwkb -lplayercommon -Wl,-rpath,/usr/local/lib

test: testRobot.cpp robot.cpp
	$(CC) $(FLAGS) $(LIBS) -o $@ $^

robot.o: robot.cpp
	$(CC) $(FLAGS) $(LIBS) -c $^ -o $(PROJECT_BIN)/$@



