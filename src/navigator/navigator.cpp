#include "navigator.h"
#include "coordinate.h"
#include "map.h"
	#include <vector>
	#include <stack>
	#include <limits>
	#include <iostream>
#define ROOT_INDEX 0;
using namespace std;
/*----node stuff ----*/
Navigator::node::node(){
	_coord = coordinate(0,0,0,0);
	_parent = NULL;
	_index = 0;
};

Navigator::node::node(coordinate coord, node * parent, int index){
	_coord = coord; _parent = parent; _index = index;
};

coordinate Navigator::node::coord(){ return _coord;};

Navigator::node Navigator::node::parent(){ 
	if(this->is_root()) return *this;
return *_parent;
};

int Navigator::node::index(){return _index;};

bool Navigator::node::is_root(){ return _index == 0;};

bool Navigator::node::is_valid(){ return (_index >= 0) && (_parent >= 0);}

/*********navigator stuff***************/
Navigator::Navigator(Map * map, coordinate root){
	//set the map
	_map = map;
	robot_location = root;
	last_location = root;	
	failed_attempts = 0;
	waypoints.push(root);

};

bool Navigator::save_position(coordinate location, coordinate last_location){
if(waypoints.contains(location)) return false;
	waypoints.push(location);	
return true;
};

//get the waypoint at the top of the queue given the current location
	//this function assumes that the robot has either reached it waypoint
	//or completely failed to reach it. No in betweens.
coordinate Navigator::next_waypoint(coordinate current_location, bool success){
	if(waypoints.empty()) return next_goal();
	coordinate waypoint = waypoints.top();
	waypoints.pop();
return waypoint;
};

//get's the next goal checks
coordinate Navigator::next_goal(){
	//if the map has been explored then the robot is done.
	if(_map->map_explored()) return robot_location;	
	bool cond;
	//generate a new goal if the old one is inaccessible bool cond;	
	do{ 
		this->goal = _map->generate_random_coord();
		// construct the end condition
		cond = !(_map->accessible(goal));
			cond = cond && !(in_tree(goal));
			cond = cond 
				&& (coordinate::distance(goal, closest_in_tree(goal)->coord()) > 6);
	}while(cond);	
return goal;
};

void Navigator::plan_path_to_goal(coordinate goal){
	//add the goal coordinate to the waypoint stack
	waypoints.push(goal);	

	//find the closest node in the tree to goal
	node n = *closest_in_tree(goal);
	//add that node's coordinate to the waypoint stack
	waypoints.push(n.coord());
	//while the current node is not the root node
	while(!n.is_root()){
		//set the current node to be the current node's parent
		n = n.parent();
		//add the current node's coordinate to the waypoint stack
		waypoints.push(n.coord());
		if(coordinate::near(robot_location, n.coord())) return;
	}
	//create a new stack called sub_stack NOT replacing the waypoint stack
	std::stack<coordinate> s;
	//find the closest node in the tree to the current location
	n = *closest_in_tree(robot_location);
	//add that node's coordinate to the sub_stack
	s.push(n.coord());
	//while the current node is not the root node
	while(!n.is_root()){
		//set the current node to be the current node's parent
		n = n.parent();
		//add the current node's coordinate to the sub_stack
		s.push(n.coord());
	}
	//until the sub_stack is empty
	while(!s.empty() && s.top() != tree[0]->coord()){
		//add the front of the sub_stack to the waypoint stack
		waypoints.push(s.top());
		//pop the front of the sub_stack
		s.pop();
	}
};

//create a new node and add it to the tree
void Navigator::add_node(coordinate coord, node * parent){
	if(in_tree(coord)) return;
	if(parent != NULL)
		if( coordinate::near(coord, parent->coord()) ) return;
	tree.push_back(new node(coord, parent, tree.size()));
};

//checks to see if the coordinate is in the tree
bool Navigator::in_tree(coordinate coord){
//if the find_node function returns NULL return false
return find_node(coord) != NULL;
};

//finds the node with the coresponding coordinate
Navigator::node * Navigator::find_node(coordinate coord){
	if(tree.empty()) return NULL;
	//for each element in tree 
		//if the coordinate matches return the tree
	for(unsigned i = 0; i < tree.size(); i++)
		if( coordinate::near(tree[i]->coord(), coord) ) return tree[i];
//all else fails return null
return NULL;
};

Navigator::node * Navigator::closest_in_tree(coordinate goal){
	node * closest = tree[0]; 
	double lowest_distance = std::numeric_limits<double>::max();
	for(unsigned i = 0; i < tree.size(); i++){
		node * n = tree[i]; 
		double cur_dist = coordinate::distance(goal, n->coord()); 
		if(cur_dist < lowest_distance){
			lowest_distance = cur_dist;
			closest = tree[i];
		}
	}
return closest;
};

void Navigator::print_tree(){
	//for each element in the tree
		//print the coordinate and the index of it's parent

	for(unsigned i = 0; i < tree.size(); i++){
		node n = *tree[i];
		(n.coord()).print();
		std::cout << "\tparent index:"
				  << n.parent().index()  
				  << std::endl;
	}		
};

coordinate Navigator::get_goal(){ return this->goal; };

void Navigator::print_waypoints(){ waypoints.print();}

