#ifndef ROBO_NAVIGATOR_H
#define ROBO_NAVIGATOR_H
#include "map.h"
#include "coordinate.h"
	#include <vector>
	#include "stack.h"

class Navigator{
public:
	Navigator(Map * map, coordinate root);
	
	void print_tree();
	//get the waypoint at the top of the queue given the current location
	coordinate next_waypoint(coordinate location);

//private:
//a node
	typedef struct node{
		coordinate coord;
		int parent;
		unsigned index;
	} node;
		
	std::vector<node> tree;
	void add_node(coordinate coord, int parent_index);
	bool in_tree(coordinate coord);
	bool root_node(node n);
	//returns the index of the nodes
		//pointers change in a vector duh
	int find_node(coordinate coord);
	int closest_in_tree(coordinate goal);

	//the queue of waypoints that the robot follows
		//to meet its goals
	stack waypoints;
	coordinate robot_location;
	Map * _map;
	
	//looks at the map and returns the coordinate of the next goal.
		//next goal should be unexplored.
	coordinate next_goal();
		void plan_path_to_goal(coordinate goal);

};
#endif
