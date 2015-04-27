#include "coordinate.h"
#include <cmath> 

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
	double X = std::pow( (coordA.x - coordB.y), 2);
	double Y = std::pow( (coordA.y - coordB.y), 2);
	double Z = std::pow( (coordA.z - coordB.z), 2);
return std::sqrt(X + Y + Z);
}
