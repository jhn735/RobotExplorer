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
	coordinate prev_loc = position();
	
	if(obstacle_present()){ cout << "swiper no swiping" << endl; return false;}
	while(!obstacle_present()){
		if(!move(1)) break;
	}
	if(!coordinate::near(position(), prev_loc)){
		last_position = prev_loc;
		navi->save_position(position(), last_position);
	}
return true;
};

bool Robot::go_to(coordinate dest){
last_position = position();
bool retVal;
	cout << "Going to "; dest.print();
	if(position() == dest) return true;
	//have the robot turn toward the destination
	retVal = turn_toward(dest);
	if(!retVal) return retVal;
	
	double distance = coordinate::distance(position(), dest);

	//if no obstacles around
		//move to the destination
	if(!obstacle_present())
		retVal = move(distance);
	else return false;
	
	//if the movement was successful go again
		//just for fun

 navi->save_position(position(), last_position);
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
		
		//if there is something in the way turn for 
		if(obstacle_present()) {
			while(!obstacle_present(FRONT_SIDE))
				pos->SetSpeed(0, yaw_speed_mid);
			stop();
			if(!move(1));
		};
		
		//set the speed to low or high depending on the threshold
			//making sure to turn in the right direction.
			if(ang_dist < yaw_speed_thresh*3) speed = yaw_speed_mid;
			if(ang_dist < yaw_speed_thresh) speed = yaw_speed_low;
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
cout << "\tMoving distance:" << distance << endl;
//if there is nowhere to move return true;
	if(distance == 0) return true;
	//to keep track of the distance covered
	coordinate pos0 = position();
	
	pos->SetSpeed(movement_speed, 0);
	
	double dist;
	
	coordinate lpos = position();	
	while(true){
		//stop and smell the roses
		client->Read();
		
		//get the distance
		dist = coordinate::distance(position(), pos0);
		//save the current position every fourth of the way there
		if(distance > 8)
			if( ((int)dist)%((int)(distance/4)) == 0){
				navi->save_position(position(), lpos);
				lpos = position();
			}
		
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
	cout << "\tTaking a step back!" << endl;			
	pos->SetSpeed(-movement_speed, 0);
			sleep(1);
			stop();
};
bool Robot::obstacle_present(){
	return obstacle_present(0, laser->GetCount());
};

bool Robot::obstacle_present(int range1, int range2){
	client->Read();
	for(int i = range1; i < range2; i++){
		if(laser->GetRange(i) <= robot_min_range) return true;
	} 
return false;
};

bool Robot::obstacle_present(int side){
	switch(side){
		case FRONT_SIDE:{
			int range1 = laser->GetCount()/2 - laser->GetCount()/8;
			int range2 = laser->GetCount()/2 + laser->GetCount()/8;
		return obstacle_present(range1, range2);	
		};	
		
		case LEFT_SIDE:{
		return laser->GetMinLeft() < robot_min_range;
		};
		
		case RIGHT_SIDE:{
		return laser->GetMinRight() < robot_min_range;
		};
	};
return obstacle_present();
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
    cout << "*Dora has started exploring!" << endl;
    cout << "Dora: \"Vamonos!\"" << endl;
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

		
		cout << "***************" << endl;
		
		//set the last position
		last_position = position();
		//start by going to the x waypoint
			//if that doesn't work go back and try the y
		if(!go_to(x_waypoint)){
			go_to(last_position);
			//if going to the y waypoint doesn't work then go back.
			if(!go_to(y_waypoint)){
				go_to(last_position);
			}else success = go_to(waypoint);
		}else success = go_to(waypoint);
		
		success = go_to(waypoint);
		
		//every once in a while explore
		//double r = rand_between(0, 10, 1);
		
		success = !explore(); 	
			
		if(success) cout << endl << "Reached waypoint!" << endl;
		else cout << endl << "Failed to reach waypoint!" << endl;
		
		cout << endl << "#####WAYPOINTS#####" << endl;
		navi->print_waypoints();
		cout << endl << "###################" << endl;

		cout << endl << "+++++TREE++++++" << endl;
		navi->print_tree();
		cout << endl << "+++++++++++++++" << endl;
		
		//print the status of the map
		cout << endl <<"******MAP********" << endl;
		map->print_section_map();
		cout << "*****************" << endl;
		
	};
	cout << "We did it. We dit it. Horay!!!" << endl;
	
  }
  catch (PlayerCc::PlayerError & err)
  {
    std::cerr << err << std::endl;
    return;
  }
};


