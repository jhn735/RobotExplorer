/*
	Having something that stores coordinates together is much convenient wow.
*/
#ifndef ROBO_COORDINATE_H
#define ROBO_COORDINATE_H
class coordinate{
public:
	coordinate();
	coordinate(double x_, double y_, double z_, double theta_);
	static double distance(coordinate coordA, coordinate coordB);

	//the coords
	double x;	double y;	double z;
	double theta;
};

#endif
