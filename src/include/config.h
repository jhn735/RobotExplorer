/*
	We define some constants here to make things easier to tweak, if necessary.
*/
#ifndef ROBO_CONFIG_H
#define ROBO_CONFIG_H
	//robot's size
	#define ROBOT_LENGTH_METERS 0.44
	#define ROBOT_WIDTH_METERS 0.38
	#define ROBOT_HEIGHT_METERS 0.22
	
	#define ROBOT_MIN_RANGE 0.75
	#define ROBOT_COORD_RANGE 0.1

	//robots starting position in meters3 and degrees
		//respectively
	#define ROBOT_STARTPOS_X -6.432
	#define ROBOT_STARTPOS_Y -5.895
	#define ROBOT_STARTPOS_Z 0
	#define ROBOT_STARTPOS_THETA 45

	//the default speed of movement for robot
	#define ROBOT_YAW_SPEED 0.5
	#define ROBOT_MOVEMENT_SPEED 0.5

	//map's conversion facter of pixels to meters
	#define MAP_PIXELS_PER_METER 36.995
#endif

