#include "navigator.h"
#include "coordinate.h"
#include "map.h"
Navigator::Navigator(){

};

//get the waypoint at the top of the queue given the current location
coordinate Navigator::next_waypoint(coordinate current_location){
	//if the waypoint has been reached remove from queue
		//otherwise the robot was blocked
		//and a plan to the next waypoint should be made.
	if(robot_location == waypoints.front()) waypoints.pop();
	else plan_path_to_goal(waypoints.front());	

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
	coordinate retVal = waypoints.front();
return retVal;
};

coordinate Navigator::next_goal(){
	if(_map->map_explored()) return robot_location;	

}
