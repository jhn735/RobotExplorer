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
	
	static const int FRONT_SIDE = 0;
	static const int LEFT_SIDE = 1;
	static const int RIGHT_SIDE = 2;
	
	static const double yaw_speed_high = ROBOT_YAW_SPEED_HIGH;
	static const double yaw_speed_mid = ROBOT_YAW_SPEED_MID;
	static const double yaw_speed_low = ROBOT_YAW_SPEED_LOW;
	static const double yaw_speed_thresh = ROBOT_YAW_SPEED_THRESHOLD;
	static const double yaw_range = 0.1;
	static const double movement_speed = ROBOT_MOVEMENT_SPEED;
	static const double robot_min_range = ROBOT_MIN_RANGE;	
	coordinate position();
	coordinate last_position;
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
	//explore goes on until an obstacle is found
	bool explore();
	//has robot goto to the specified point
	bool go_to(coordinate dest);
	//directions Forward and backward should not work here. 
	bool turn_toward(coordinate dest);
	bool turn(double radians);
	//move forward a certain distance. to move backward set distance to negative
	bool move(double distance);
	//stops the robot	
	void stop();
	//makes the robot move back a bit
	void step_back();
	//checks to see if there is an obstacle
	bool obstacle_present();
	bool obstacle_present(int side);
	bool obstacle_present(int range1, int range2);
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
