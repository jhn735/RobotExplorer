#ifndef ROBO_NAVIGATOR_H
#define ROBO_NAVIGATOR_H
#include "map.h"
#include "coordinate.h"
#include <queue>

class Navigator{
	//the queue of waypoints that the robot follows
		//to meet its goals
	queue<coordinate> waypoints;
	coordinate robot_location;
	Map * _map;
	
	//looks at the map and returns the coordinate of the next goal.
		//next goal should be unexplored.
	coordinate next_goal();
		void plan_path_to_goal(coordinate goal);

public:
	Navigator(Map * map);

	//get the waypoint at the top of the queue given the current location
	coordinate next_waypoint(coordinate location);

};

#endif
