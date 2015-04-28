#include "navigator.h"
#include "coordinate.h"
#include "map.h"
	#include <vector>
	#include <stack>

using namespace std;
Navigator::Navigator(Map * map, coordinate root){
	//set the map
	_map = map;

	//construct the root node and add it to the tree
	node root_node;
		root_node.coord = root;
		root_node.parent = NULL;	
	tree.push_back(root_node);
};

//get the waypoint at the top of the queue given the current location
coordinate Navigator::next_waypoint(coordinate current_location){
	//if the waypoint has been reached remove from queue
		//otherwise the robot was blocked
	if(robot_location == waypoints.top()) waypoints.pop();

	//set the robot_location to be location.
	robot_location = current_location;
	
	//if the queue is empty
		//get the next goal
		//plan the path to that goal
	if(waypoints.empty()){
		coordinate goal = next_goal();
		plan_path_to_goal(goal);
	}
	
	//get and remove the next element in the waypoint queue
	coordinate retVal = waypoints.top();
return retVal;
};

//get's the next goal checks
coordinate Navigator::next_goal(){
	//if the map has been explored then the robot is done.
	if(_map->map_explored()) return robot_location;	

	//generate a new goal if the old one is inaccessible
	coordinate goal; bool cond;	
	do{ 
		goal = _map->generate_random_coord();
		// construct the 
		cond = !(_map->accessible(goal));
			cond = cond && !(in_tree(goal));
	}while(cond);	

return goal;
};

void Navigator::plan_path_to_goal(coordinate goal){
	//add the goal coordinate to the waypoint stack
	
	//find the closest node in the tree to goal
		//hint map has a distance finding function
	//add that node's coordinate to the waypoint stack
	//while the current node is not the root node
		//set the current node to be the current node's parent
		//add the current node's coordinate to the waypoint stack
	
	//create a new stack called sub_stack NOT replacing the waypoint stack
	//find the closest node in the tree to the current location
	//add that node's coordinate to the sub_stack
	//while the current node is not the root node
		//set the current node to be the current node's parent
		//add the current node's coordinate to the sub_stack
	
	//until the sub_stack is empty
		//add the front of the sub_stack to the waypoint stack
		//pop the front of the sub_stack


};

//create a new node and add it to the tree
void Navigator::add_node(coordinate coord, node * parent){
	node n;
		n.coord = coord;
		n.parent = parent;
	tree.push_back(n);
};


//checks to see if the coordinate is in the tree
bool Navigator::in_tree(coordinate coord){
	//for each element in tree 
		//if the coordinate matches return true
	for(int i = 0; i < tree.size(); i++)
		if(tree[i].coord == coord) return true;
//all else fails return false
return false;
};

int Navigator::get_index(coordinate coord){
	//for each element in tree
		//if the coordinate matches return the index
	for(int i = 0; i < tree.size(); i++)
		if(tree[i].coord == coord) return i;
};

void Navigator::print_tree(){
	//for each element in the tree
		//print the coordinate and the index of it's parent
};
