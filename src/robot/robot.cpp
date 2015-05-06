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
cout << "Exploring!" << endl;
	if(obstacle_present()) return false;
	while(!obstacle_present()){
		move(1);
	}
return true;
};

bool Robot::go_to(coordinate dest){
bool retVal;
	cout << "Going to "; dest.print();
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
	std::cout << "\t::Turning::" << endl;
	//get the new angle
	coordinate posi = position();
	double angle = coordinate::angle_towards(posi, dest);
	cout << "\tturning to angle " << angle << "rad" << endl;
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
		
		//set the speed to low or high depending on the threshold
			//making sure to turn in the right direction.
			if(ang_dist < ROBOT_YAW_SPEED_THRESHOLD) speed = yaw_speed_low;
			else{ speed = yaw_speed_high; }
			if((angle - pos->GetYaw()) < 0) speed *= -1;
		pos->SetSpeed(0, speed);
	}

//if somehow execution reaches here stop the robot. 
	//Go home computer, you're drunk.
	stop();
return false;
};

bool Robot::move(double distance){
cout << "\t::Moving::" << endl;
//if there is nowhere to move return true;
	if(distance == 0) return true;
	//to keep track of the distance covered
	coordinate pos0 = position();
	
	pos->SetSpeed(movement_speed, 0);
	
	double dist;
	
	while(true){
		//stop and smell the roses
		client->Read();
		//get the distance
		dist = coordinate::distance(position(), pos0);
		//save the current position
		//navi->save_position(position(), last_position);
		//report location to map
		map->mark_explored(position());
		//if there is an obstacle stop;
		if(obstacle_present()){	
			stop(); 
			step_back();
			return false;
		}

		//if the distance has been covered stop
		if( dist >= distance){
		 stop(); 
		 return true;
		 }
	};

	//if somehow execution reaches here stop the robot. 
		//Go home computer, you're drunk.
	stop();
return false;
};

void Robot::stop(){ pos->SetSpeed(0,0); };

void Robot::step_back(){ 			
	pos->SetSpeed(-movement_speed, 0);
			sleep(1);
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
	
	last_position = position();
	//while there is still places to go in map
	while(!map->map_explored()){
		//stop the robot just in case
		stop();
		client->Read();
		
		//print the current position
		std::cout << "Position: ";
		position().print();

		//get the next waypoint
		coordinate waypoint = navi->next_waypoint(position(), success);

		//print waypoint
		cout << "Waypoint: "; waypoint.print();
		
		if(last_waypoint == waypoint) sameCount++;
		else{ last_waypoint = waypoint; sameCount = 0;}
		
		//split the waypoint in x and y
		coordinate cur_pos = position();
		coordinate x_waypoint(waypoint.x, cur_pos.y, 0, 0);
		coordinate y_waypoint(cur_pos.y, waypoint.x, 0, 0);
		
		//print the x and y waypoint 
		cout << "XWaypoint:"; x_waypoint.print();
		cout << "YWaypoint:"; y_waypoint.print();
		
		cout << "Navi's goal:"; navi->get_goal().print();
		//set the last position
		last_position = position();
		
		cout << "***************" << endl;
		
		//start by going to the x waypoint
			//if that doesn't work go back and try the y
		if(!go_to(x_waypoint)){
			navi->save_position(position(), last_position); 
			go_to(last_position);
			//if going to the y waypoint doesn't work then go back.
			if(!go_to(y_waypoint)){
				navi->save_position(position(), last_position);
				go_to(last_position);
			}
		}
		
		navi->save_position(position(), last_position);
		success = go_to(waypoint);
		
		if(success) cout << endl << "Reached waypoint!" << endl;
		
		//every once in a while explore
		double r = rand_between(0, 10, 1);
		if(r > 6){ 
			success = !explore(); 	
		}
		
		cout << endl << "+++++TREE++++++" << endl;
		navi->print_tree();
		cout << endl << "+++++++++++++++" << endl;
		
		//print the status of the map
		cout << endl <<"******MAP********" << endl;
		map->print_section_map();
		cout << "*****************" << endl;
		
	};
	
  }
  catch (PlayerCc::PlayerError & err)
  {
    std::cerr << err << std::endl;
    return;
  }
};


