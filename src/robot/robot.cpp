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

bool Robot::turn(double angle, direction d){
	if(d == FORWARD || d == BACKWARD) return false;
	double new_yaw = yaw+angle;
};
