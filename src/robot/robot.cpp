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
	#include <limits>
	#include <vector>
using namespace std;
using namespace PlayerCc;
Robot::Robot(Map * m){
	//set the map
	this->map = m;
	//initialization of the navigator
		//will take place in the run function
}

coordinate Robot::position(){
	client->Read();
	double x = pos->GetXPos();
	double y = pos->GetYPos();
	double theta = pos->GetYaw();
	
return coordinate(x, y, 0, theta);
};

//explore in a straight path
bool Robot::explore(double direction){
cout << "Exploring!" << endl;
	stop();
	//if the direction has been explored don't save the postion no need to explore
		//otherwise swiper no swiping return false;
	if(!direction_explored(direction)){
		navi->save_position(position(), position());
		//turn to the direction in which to go exploring.
		turn_to(direction);
		//if there isn't anything in the way move
		if(!obstacle_present()) move(exploring_distance);
	}else{ cout << "swiper no swiping" << endl; return false;}

	//make sure the robot has stopped;
	stop();
	//setup the four directions 
	double directions[] = {UP, RIGHT, DOWN, LEFT};
	//update sensor readings
	client->Read();
	
	coordinate pos1;
	vector<double> possible_dirs;

	double range;
	bool explored;
	//turn toward each of the four directions
	for(int i = 0; i < 4; i++){
		double cur_direction = directions[i];
	//if the current direction is not explored explore it. vamonos!
		//and print map
		if(!direction_explored(cur_direction)){			
			explore(cur_direction);
			map->print_section_map();	
		}
	}
	
return true;
};

bool Robot::direction_explored(double direction){
	double range;
	bool explored;
		client->Read();
		//get the coordinate
		coordinate pos1 = position();
		
		//get the coordinate of the robot if it went in that direction
		if(direction == UP){
			turn_to(UP);
			client->Read();
			range = laser->GetRange(180)-robot_min_range;
			pos1.y += range;
		}
		if(direction == DOWN){
			turn_to(DOWN);
			client->Read();
			range = laser->GetRange(180)-robot_min_range;
			pos1.y -= range;
		}
		
		if(direction == RIGHT){
			turn_to(RIGHT);
			client->Read();
			range = laser->GetRange(180)-robot_min_range;
			pos1.x += range;
		}
		
		if(direction == LEFT){
			turn_to(LEFT);
			client->Read();
			range = laser->GetRange(180)-robot_min_range;
			pos1.x -= range;
		}
		
		if(range < exploring_distance) return true;
		cout<< "proposed coordinate: "; pos1.print();
		explored = map->coord_explored(pos1); 
		cout << "explored? " << explored << endl;
	
return explored;
};
bool Robot::go_to(coordinate dest){
last_position = position();
bool retVal;
	cout << "Going to "; dest.print();
	if(coordinate::near(position(), dest)) return true;
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

//turn to a certain amount of radians
bool Robot::turn_to(double radians){
	std::cout << "\t::Turning to " << radians << "rads::" << endl;
	double ang_dist;				
	double speed;
	double angle = radians;

	while(true){
		//stop and smell the roses
		client->Read();
		
		//cout << "cur_yaw" << pos->GetYaw();
		//find the distance between the current Yaw and the goal angle
		ang_dist = std::abs(angle - pos->GetYaw());
		
		//if the distance is within range. break success
		if(ang_dist <= yaw_range){ stop(); return true;}
		
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
	
	while(true){
		//stop and smell the roses
		client->Read();
		
		//get the distance
		dist = coordinate::distance(position(), pos0);
		
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
	pos->SetSpeed(-robot_min_range, 0);
			sleep(1);
			stop();
			
	client->Read();
	double yaw = pos->GetYaw();
	
	cout << "\t turning away from the obstacle" << endl;
	while(obstacle_present(FRONT_SIDE, robot_min_range*2)){
		client->Read();
		pos->SetSpeed(0, yaw_speed_mid); 	
	}
	//if dora turned at all then move forward
	if(std::abs(yaw - pos->GetYaw()) > PI/4){
		cout << "\t moving away from obstacle" << endl;
		pos->SetSpeed(robot_min_range, 0);
				sleep(1);
				stop();
	}

};

bool Robot::obstacle_present(int range1, int range2, double range){
	client->Read();
	for(int i = range1; i < range2; i++){
		if(laser->GetRange(i) <= range) return true;
	} 
return false;
};

bool Robot::obstacle_present(int side, double range){
	switch(side){
		case FRONT_SIDE:{
			int range1 = laser->GetCount()/2 - laser->GetCount()/10;
			int range2 = laser->GetCount()/2 + laser->GetCount()/10;
		return obstacle_present(range1, range2, robot_min_range);	
		};	
		case LEFT_SIDE:{
		return laser->GetMinLeft() < robot_min_range;
		};
		case RIGHT_SIDE:{
		return laser->GetMinRight() < robot_min_range;
		};
	};
//if all else fails just return the default
return obstacle_present();
};


double Robot::max_range(int side){	
client->Read();
int range1 = 0; int range2 = 0;
	int count = laser->GetCount();
	switch(side){
		case FRONT_SIDE:{
			range1 = count/2 - count/15;
			range2 = count/2 + count/15;

		};	
		case LEFT_SIDE:{
			range1 = 0;
			range2 = count/2;
		};
		
		case RIGHT_SIDE:{
			range1 = count/2;
			range2 = count;
		};
	};
	
	double current_max = 0;
	double current_range;
	//from range 1 to range 2 
		//find the max
	for(int i = range1; i < range2; i++){
		current_range = laser->GetRange(i);
		if(current_range > current_max) current_max = current_range;
	} 
return current_max;
};

bool Robot::obstacle_present(){
return obstacle_present(FRONT_SIDE, robot_min_range) 
	|| obstacle_present(0, 20, robot_min_range*0.75)
	|| obstacle_present(340, 360, robot_min_range*0.75) ;
};

bool Robot::obstacle_present(int side){
return obstacle_present(side, robot_min_range);
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

	last_position = position();
	
	//while there is still places to go in map
	while(!map->map_explored()){
		//stop the robot just in case
		stop();
		client->Read();


		//get the next waypoint
		waypoint = navi->next_waypoint(position(), success);
		//split the waypoint in x and y
		coordinate cur_pos = position();
		coordinate x_waypoint(waypoint.x, cur_pos.y, 0, 0);
		coordinate y_waypoint(cur_pos.y, waypoint.x, 0, 0);
		
		//print the current status of the robot.
		print_status();
		
		
		//set the last position
		last_position = position();
		//if already at the waypoint get another one
		if(coordinate::near(waypoint, position()))
			waypoint = navi->next_waypoint(position(), success);
		

		//start by going to the x waypoint
		//if that doesn't work go back and try the y
		if(!go_to(x_waypoint)){
			go_to(last_position);
			//if going to the y waypoint doesn't work then go back.
			if(!go_to(y_waypoint)){
				go_to(last_position);
			}else success = go_to(waypoint);
		}else success = go_to(waypoint);
		//check if the robot can successfully reach the waypoint
		success = go_to(waypoint);

		
		//explore!
		cout << "direction: " << UP << endl;
		success = !explore(UP);
				
	};
	cout << "We did it. We dit it. Horay!!!" << endl;
	
  }
  catch (PlayerCc::PlayerError & err)
  {
    std::cerr << err << std::endl;
    return;
  }
};

void Robot::print_status(){
		
		//print the current position
		std::cout << "Position: "; position().print();
		
		//print waypoint
		cout << "Waypoint: "; waypoint.print();
		
		cout << endl << "#####WAYPOINTS#####" << endl;
		navi->print_waypoints();
		cout << endl << "###################" << endl;

		//print the status of the map
		cout << endl <<"******MAP********" << endl;
		map->print_section_map();
		cout << "*****************" << endl;

};


