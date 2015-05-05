#include "robot.h"
#include "config.h"
#include "coordinate.h"
#include "map.h"
#include "utils.h"
	#include <libplayerc++/playerc++.h>
	#include <cmath>
	#include <cstdlib>
	#include <stdint.h>
	#include <unistd.h>
using namespace std;
using namespace PlayerCc;
Robot::Robot(Map * m){
	//set the map
	this->map = m;
	//initialization of the navigator
		//will take place in the run function
}

coordinate Robot::position(){
	double x = pos->GetXPos();
	double y = pos->GetYPos();
	double theta = pos->GetYaw();
	
return coordinate(x, y, 0, theta);
};
//explore in a straight path
bool Robot::explore(){
	if(obstacle_present()) return false;
	while(!obstacle_present())
		move(1);
		
return true;
};

bool Robot::go_to(coordinate dest){
bool retVal;
	if(position() == dest) return true;
	//have the robot turn toward the destination
	retVal = turn_toward(dest);
	if(!retVal) return retVal;
	
	double distance = coordinate::distance(position(), dest);
	//cout << "distance:" << distance << endl;

	//if no obstacles around
		//move to the destination
	if(!obstacle_present())
		retVal = move(distance);
	else return false;
	
	//if the movement was successful go again
		//just for fun

	
return retVal;
};

bool Robot::turn_toward(coordinate dest){
	std::cout << "turning" << endl;
	//get the new angle
	coordinate posi = position();
	double angle = coordinate::angle_towards(posi, dest);
	cout << "angle" << angle << endl;
	double ang_dist;				
	double speed;

	while(true){
		//stop and smell the roses
		client->Read();
		
		//cout << "cur_yaw" << pos->GetYaw();
		//find the distance between the current Yaw and the goal angle
		ang_dist = std::abs(angle - pos->GetYaw());
		
		//if the distance is within range. break success
		if(ang_dist <= yaw_range){ stop(); return true;}
		
		//if there is something in the way go backwards for a bit
		if(obstacle_present()) {
			step_back();
		};
		
		//set the speed proportional to the angle distance 
			//making sure to turn in the right direction.
			speed = yaw_speed*ang_dist;
			if(speed < 0.1) speed = 0.1;
			if((angle - pos->GetYaw()) < 0) speed *= -1;
		pos->SetSpeed(0, speed);
	}

//if somehow execution reaches here stop the robot. 
	//Go home computer, you're drunk.
	stop();
return false;
};

bool Robot::move(double distance){
cout << "moving" << endl;
//if there is nowhere to move return true;
	if(distance == 0) return true;
	//to keep track of the distance covered
	coordinate pos0 = position();
	
	pos->SetSpeed(movement_speed, 0);
	
	while(true){
		//stop and smell the roses
		client->Read();
		//report location to map
		map->mark_explored(position());
		//if there is an obstacle stop;
		if(obstacle_present()){	
			stop(); 
			step_back();
			return false;
		}
		//if the distance has been covered stop
		if( coordinate::distance(position(), pos0) >= distance){
		 stop(); 
		 return true;}
	};

	//if somehow execution reaches here stop the robot. 
		//Go home computer, you're drunk.
	stop();
return false;
};

void Robot::stop(){ pos->SetSpeed(0,0); };

void Robot::step_back(){ 			
	pos->SetSpeed(-movement_speed, 0);
			sleep(2);
			stop();
};
bool Robot::obstacle_present(){
	//iterate through all points in the scan
		//it it is less than the allotted range return true
	int count = laser->GetCount();
	for(int i = 0; i < count; i++){
		if(laser->GetRange(i) <= robot_min_range) return true;
	} 
	
return false;
};

//the piece de resistance
void Robot::run(){
std::string  gHostname(PlayerCc::PLAYER_HOSTNAME);
uint32_t        gPort(PlayerCc::PLAYER_PORTNUM);
uint32_t        gIndex(0);

//let the games begin
try
  {
    using namespace PlayerCc;
//set up the robot control stuff
    PlayerClient robo(gHostname, (uint32_t)gPort);
     	client = &robo;
    Position2dProxy pp(client, (uint32_t)gIndex);
    	pos = &pp;
    LaserProxy lp(client, (uint32_t)gIndex);

    	laser = &lp;


    pos->SetMotorEnable (true);
	client->Read();
	//initialize the navigator
	navi = new Navigator(map, position()); 
	//report the current location of the robot to map
	map->mark_explored(position());
	
	bool success = true; 
	coordinate last_waypoint = position();
	int sameCount = 0;
	//while there is still places to go in map
	while(!map->map_explored()){
		client->Read();
		std::cout << "position:";
		position().print();
		//print the status of that venture
		cout << endl << success << endl;
		//get the next waypoint
		coordinate waypoint = navi->next_waypoint(position(), success);

		//print waypoint
		cout << "waypoint:"; waypoint.print();
		if(last_waypoint == waypoint) sameCount++;
		else{ last_waypoint = waypoint; sameCount = 0;}
		//go to said waypoint
		success = go_to(waypoint);
		
		//every once in a while explore
		double r = rand_between(0, 10, 1);
		if(r > 8) success = !explore();
		
		//print the status of that venture
		cout << endl << success << endl;
		//print the status of the map
		//map->print_section_map();
		
	};
	
  }
  catch (PlayerCc::PlayerError & err)
  {
    std::cerr << err << std::endl;
    return;
  }
};


