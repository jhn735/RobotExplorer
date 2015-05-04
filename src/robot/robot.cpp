#include "robot.h"
#include "config.h"
#include "coordinate.h"
#include "map.h"
	#include <libplayerc++/playerc++.h>
Robot::Robot(Map * m, coordinate start_pos){
	position = start_pos;
	//set the map
	this->map = m;
	//initialize the navigator
	navi = new Navigator(map, position);
	
	
}

bool Robot::turn(double angle, direction d){
	if(d == FORWARD || d == BACKWARD) return false;
	double new_yaw = yaw + angle;
	while(yaw <= new_yaw + 0.01 || yaw >= new_yaw + 0.01){
		
	}
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

	uint32_t gIndex(0);

try
  {
    using namespace PlayerCc;

    client = new PlayerClient(PLAYER_HOSTNAME, PLAYER_PORTNUM);
    pos = new Position2dProxy(client, gIndex);
    laser = new LaserProxy(client, gIndex);

    std::cout << *client << std::endl;

    pos.SetMotorEnable (true);

    // go into read-think-act loop
    for(;;)
    {

    }
  }
  catch (PlayerCc::PlayerError & e)
  {
    std::cerr << e << std::endl;
    return -1;
  }
}

};
