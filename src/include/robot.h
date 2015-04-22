#include "config.h"
#include "coordinate.h"
#ifndef ROBO_ROBO_H
#define ROBO_ROBO_H
class Robot{
private:
	coordinate position;

public:
	Robot(){
		position = coordinate(
			ROBOT_STARTPOS_X,
			ROBOT_STARTPOS_Y,
			ROBOT_STARTPOS_Z,
			ROBOT_STARTPOS_THETA );
		
	};
	~Robot();

//dimensions of the robot in meters
	static double length(){ return ROBOT_LENGTH_METERS;};
	static double width(){ return ROBOT_WIDTH_METERS;};
	static double height(){ return ROBOT_HEIGHT_METERS;};

//directions robot my move or turn in. 
	enum direction { FORWARD, BACKWARD, LEFT, RIGHT};

	/* Position modifying functions
		*Negative number changes direction to opposite of specified.
		*Returns true if operation was successful
	*/
	//directions Forward and backward should not work here. 
	bool turn(double angle, direction d);
	//directions RIGHT and LEFT may or may not work here.
	bool move(double distance, direction d);
};
#endif
