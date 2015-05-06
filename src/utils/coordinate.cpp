#include "coordinate.h"
#include "config.h"
#include <cmath> 
#include <iostream>
#define PI          3.1415 /* pi */
/*
	Having something that stores coordinates together is much convenient wow.
*/
coordinate::coordinate(){
	x = 0; y = 0; z = 0;
	theta = 0;
};

coordinate::coordinate(double x_, double y_, double z_, double theta_){
	x = x_; y = y_; z = z_;
	theta = theta_;
};

//discounts theta, returns the length of the line between the two coords
double coordinate::distance(coordinate coordA, coordinate coordB){
	double X = std::pow( (coordA.x - coordB.x), 2);
	double Y = std::pow( (coordA.y - coordB.y), 2);
	double Z = std::pow( (coordA.z - coordB.z), 2);
return std::sqrt(X + Y + Z);
};

double coordinate::angle_towards(coordinate src, coordinate dest){
	//pretend that src is the origin of it's own plane
	//get the difference, this is the same as setting the origin to src
	coordinate diff = dest - src;
	if(diff.x < 0.1 && diff.x > -0.1)
		if(diff.y < 0) return -PI/2;
		else if(diff.y > 0) return PI/2;
		else if(diff.y == 0) return src.theta;
		
	//get the angle between them
	double a = atan(diff.y/diff.x);
	
	//factor in the quadrant
	if( (diff.x > 0) && (diff.y > 0) ) return a;
	if( (diff.x < 0) && (diff.y > 0) ) return PI+a;
	if( (diff.x < 0) && (diff.y < 0) ) return a-PI;
	if( (diff.x > 0) && (diff.y < 0) ) return a;
};

bool coordinate::near(coordinate a, coordinate b){
return distance(a,b) <= ROBOT_COORD_RANGE;
};

void coordinate::print(){
	std::cout << "x:" << x
			  << " y:"<< y 
			  << " z:"<< z 
			  << " theta:" << theta 
			  << std::endl;
};

coordinate coordinate::operator-(const coordinate &other){
	double x = this->x - other.x;
	double y = this->y - other.y;
	double z = this->z - other.z;
	double theta = this->theta - other.theta;
return coordinate(x,y,z,theta);
};

coordinate coordinate::operator+(const coordinate &other){
	double x = this->x + other.x;
	double y = this->y + other.y;
	double z = this->z + other.z;
	double theta = this->theta + other.theta;
return coordinate(x,y,z,theta);
};

bool coordinate::operator==(const coordinate &other){
	bool retVal = true;
		retVal = retVal && (this->x == other.x);
		retVal = retVal && (this->y == other.y);
		retVal = retVal && (this->z == other.z);
		retVal = retVal && (this->theta == other.theta); 
return retVal;
};

bool coordinate::operator!=(const coordinate &other){
	return !(*this == other);
};
