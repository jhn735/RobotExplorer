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
-Navigator decides the next destination and the waypoints between that destination. 

To be continue...
==================
