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
	coordinate next_waypoint(coordinate location, bool success);

//private:
//a node
	class node{
		public:
			node();
			node(coordinate coord, node * parent, int index);
			coordinate coord();
			node parent();
			int index();
			bool is_root();
			bool is_valid();

		private:
			coordinate _coord;
			node * _parent;
			int _index;

	};
	//pointers vector will from time to time change the adresses of 
		//it's elements	but certainly not the value
	std::vector<node*> tree;
	void add_node(coordinate coord, node * parent);
	bool in_tree(coordinate coord);
	bool root_node(node n);
	//returns the index of the nodes
		//pointers change in a vector duh
	node * find_node(coordinate coord);
	node * closest_in_tree(coordinate goal);

	//the queue of waypoints that the robot follows
		//to meet its goals
	stack waypoints;
	coordinate robot_location;
	coordinate last_location;
	Map * _map;
	
	//looks at the map and returns the coordinate of the next goal.
		//next goal should be unexplored.
	coordinate next_goal();
		void plan_path_to_goal(coordinate goal);

};
#endif
