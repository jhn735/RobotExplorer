#ifndef ROBO_ROBO_H
#define ROBO_ROBO_H
	#include <libplayerc++/playerc++.h>
	#include <cstdlib>
	#if !defined (WIN32) || defined (__MINGW32__)
  		#include <unistd.h>
	#endif
	#include <iostream>
	
#include "config.h"
#include "coordinate.h"
#include "map.h"
#include "navigator.h"


class Robot{
	static const double yaw_speed = ROBOT_YAW_SPEED;
	static const double movement_speed = ROBOT_MOVEMENT_SPEED;
	static const double robot_min_range = ROBOT_MIN_RANGE;	
	coordinate position();
	
	//the server client stuff for player.
		//for information on how these work go to:
		//http://playerstage.sourceforge.net/doc/Player-cvs/player
	PlayerCc::PlayerClient * client;
	PlayerCc::Position2dProxy * pos;
	PlayerCc::LaserProxy * laser;
	
	Navigator * navi;
	Map * map;

	/* Position modifying functions
		*Negative number changes direction to opposite of specified.
		*Returns true if operation was successful
	*/
	//has robot goto to the specified point
	bool go_to(coordinate dest);
	//directions Forward and backward should not work here. 
	bool turn_toward(coordinate dest);
	//move forward a certain distance. to move backward set distance to negative
	bool move(double distance);
	//stops the robot	
	void stop();
	//checks to see if there is an obstacle
	bool obstacle_present();
public:
	Robot(Map * m);
	//starts up the robot client, connects with the server etc.	
	void run();

//dimensions of the robot in meters
	static double length(){ return ROBOT_LENGTH_METERS;};
	static double width(){ return ROBOT_WIDTH_METERS;};
	static double height(){ return ROBOT_HEIGHT_METERS;};

};
#endif
