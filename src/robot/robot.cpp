#include "robot.h"
#include "config.h"
#include "coordinate.h"
#include "map.h"
#include "utils.h"
	#include <libplayerc++/playerc++.h>
	#include <cmath>
	#include <cstdlib>
	#include <stdint.h>
	#if !defined (WIN32) || defined (__MINGW32__)
		  #include <unistd.h>
	#endif
	#if !HAVE_GETOPT
  		#include <replace.h>
	#endif
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

bool Robot::go_to(coordinate dest){
bool retVal;
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
	
return retVal;
};

bool Robot::turn_toward(coordinate dest){
bool retVal = true;
	//get the new angle
	double angle = coordinate::angle_towards(position(), dest);
		double ang_dist = std::abs(angle - pos->GetYaw());	
	//if the new angle is the same as the old one return
	if(ang_dist == 0) return true;	
		
 	double speed = yaw_speed;
 	if((angle - pos->GetYaw()) > 0) speed *= -1;
	pos->SetSpeed(0, speed);	

	while(true){
		//if there is something in the way stop the robot and return failure
		if(obstacle_present()){
			retVal = false;	break;
		}
		//if the goal has been reached break;
		if(pos->GetYaw() == angle) break;
		
		double cur_ang_dist = std::abs(angle - pos->GetYaw());
		//if the distance has actually increased you overshot it. break success
		if(ang_dist < cur_ang_dist) break;
		else ang_dist = cur_ang_dist; //otherwise keep going
	}
	//stop the robot at the end
	stop();
return retVal;
};

bool Robot::move(double distance){
bool retVal = true;
//if there is nowhere to move return true;
	if(distance == 0) return true;
	coordinate pos0 = position();
	
	double speed = movement_speed;
		if(distance < 0) speed *=-1;
	pos->SetSpeed(speed, 0);
	
	while(true){
		if(obstacle_present()){
			retVal = false; break;
		}
		double cur_dist = coordinate::distance(pos0, position());
		if(cur_dist >= distance) break;
	};

	//stop the robot at the end
	stop();
return retVal;
};

void Robot::stop(){ pos->SetSpeed(0,0); };

bool Robot::obstacle_present(){
	double minR = laser->GetMinRight();
	double minL = laser->GetMinLeft();
	//if there is something within the min range return true
	return (minR <= robot_min_range) ||
			(minL <= robot_min_range);

};

//the piece de resistance

/* Some or all of the following code has been provided and repurposed with the 
	following message and conditions:
Copyright (c) 2005, Brad Kratochvil, Toby Collett, Brian Gerkey, Andrew Howard, ...
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the Player Project nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
	
	//initialize the navigator
	navi = new Navigator(map, position()); 
	//report the current location of the robot to map
	map->mark_explored(position());
	
	//while there is still places to go in map
	while(!map->map_explored()){
		client->Read();
		std::cout << "position:";
		position().print();
		//get the next waypoint
		coordinate waypoint = navi->next_waypoint(position());
		std::cout << "waypoint:";
		//print waypoint
		waypoint.print();
		//go to said waypoint
		go_to(waypoint);
		//print the status of the map
		//map->print_section_map();
		
	};
	
  }
  catch (PlayerCc::PlayerError & e)
  {
    std::cerr << e << std::endl;
    return;
  }
};


