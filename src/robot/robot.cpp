#include "robot.h"
#include "config.h"
Robot::Robot(){
	position = coordinate(
		ROBOT_STARTPOS_X,
		ROBOT_STARTPOS_Y,
		ROBOT_STARTPOS_Z,
		ROBOT_STARTPOS_THETA
	);
	
}
