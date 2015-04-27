RobotExplorer
==============

Guidelines
-----------
This projects should contain 3 main classes: 

-Robot: Translates waypoints into specific actions for the robot.   
 
-Navigator: Finds next waypoint for robot to go to.   

-Map: Holds and sorts the map data.   
 
#Robot
-Robot, given a valid waypoint, should take all actions necessary to reach 
that waypoint. If it isn't able to reached it, Robot should tell the Navigator 
that it failed and give its current location. 
 
-Robot should take care of all communication between player and stage, handling 
both the Device instance and the Player server. It would be more convenient to 
create functions such as move and rotate that in turn call the corresponding player-stage bs. 
 
-At the main function one should only need to created an instance of robot and call 
its run function. 
 
#Navigator
-Navigator decides the next destination and the waypoints between that 
destination.  

-Navigator should have a stack of waypoints for a destination to be fed to the 
robot one by one.  

-Once the stack is empty, Navigator should generate a new destination and given 
the current position, it will calculate the intermediary waypoints. 

-In terms of RDT, the parent of each node robot visits will be the next 
waypoint. Once it reaches the root node, it will do a similar operation 
starting with the destination, only reversing the stack. Inefficient but simple. 
 
#Map 
-Map takes as input a png file and processes it. 

-Map is made of sections of a size just big enough for the robot to rotate 
360 degrees 

-Map contains regions of various sizes that in turn contain sections and are 
decided to be either explorable or not explorable.
  
-Each Region should contain at least one section.

To be continued...
==================
