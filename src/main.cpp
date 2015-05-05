	#include <iostream>
	#include <libplayerc++/playerc++.h>
#include "map.h"
#include "navigator.h"
#include "robot.h"
#include "coordinate.h"
#include "config.h"
#include "utils.h"


	
int main(int argc, char **argv){
//initialize the map
Map * map = new Map("cave.png");
	
Robot rob(map);

rob.run();

}
