#ifndef ROBO_NAVIGATOR_H
#define ROBO_NAVIGATOR_H
#include "map.h"
#include "coordinate.h"
	#include <vector>
	#include <stack>

class Navigator{
	//the queue of waypoints that the robot follows
		//to meet its goals
	std::stack<coordinate> waypoints;
	coordinate robot_location;
	Map * _map;
	
	//looks at the map and returns the coordinate of the next goal.
		//next goal should be unexplored.
	coordinate next_goal();
		void plan_path_to_goal(coordinate goal);

//the tree stuff
	typedef struct node{
		coordinate coord;
		node * parent;
		unsigned parent_index;
	} node;	
	std::vector<node> tree;
	void add_node(coordinate coord, node * parent);
	bool in_tree(coordinate coord);

public:
	Navigator(Map * map, coordinate root);
	
	void print_tree();
	//get the waypoint at the top of the queue given the current location
	coordinate next_waypoint(coordinate location);
};
#endif
