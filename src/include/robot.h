#ifndef ROBO_ROBO_H
#define ROBO_ROBO_H

#include "config.h"
#include "coordinate.h"
#include "map.h"
#include "navigator.h"

	#include <iostream>
//#include <libplayerc++/playerc++.h>


class Robot{
	double yaw;
		static const double yaw_speed = ROBOT_YAW_SPEED:
		static const double movement_speed = ROBOT_MOVEMENT_SPEED;
	double x_pos;
	double y_pos;
	coordinate position;
	//directions robot my move or turn in. 
	enum direction { FORWARD, BACKWARD, LEFT, RIGHT};

	//the server client stuff for player.
		//for information on how these work go to:
		//http://playerstage.sourceforge.net/doc/Player-cvs/player
	/*PlayerClient * client;
	Position2dProxy * pp;
	LaserProxy * lp;
	*/
	Navigator * navi;
	Map * map;

	/* Position modifying functions
		*Negative number changes direction to opposite of specified.
		*Returns true if operation was successful
	*/
	//directions Forward and backward should not work here. 
	bool turn(double angle, direction d);
	//directions RIGHT and LEFT may or may not work here.
	bool move(double distance, direction d);

public:
	Robot();
	//starts up the robot client, connects with the server etc.	
	void run();

//dimensions of the robot in meters
	static double length(){ return ROBOT_LENGTH_METERS;};
	static double width(){ return ROBOT_WIDTH_METERS;};
	static double height(){ return ROBOT_HEIGHT_METERS;};

};
#endif
