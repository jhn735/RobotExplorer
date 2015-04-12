#include "config.h"
#include "coordinate.h"
#ifndef ROBO_ROBO_H
#define ROBO_ROBO_H
class Robot{
private:
	coordinate position = coordinate(
		ROBOT_STARTPOS_X,
		ROBOT_STARTPOS_Y,
		ROBOT_STARTPOS_Z,
		ROBOT_STARTPOS_THETA );

public:
	Robot();
	~Robot();

	/* Position modifying functions
		*Negative number changes direction to opposite of specified.
		*Returns true if operation was successful
	*/
	//directions Forward and backward should not work here. 
	bool turn(double angle, direction d);
	//directions RIGHT and LEFT may or may not work here.
	bool move(double distance, direction d);

//dimensions of the robot
	static const double length = ROBOT_LENGTH_METERS;
	static const double width = ROBOT_WIDTH_METERS;
	static const double height = ROBOT_HEIGHT_METERS;

//directions robot my move or turn in. 
	static enum direction { FORWARD, BACKWARD, LEFT, RIGHT};
};
#endif
