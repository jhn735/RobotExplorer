/*
	Having something that stores coordinates together is much convenient wow.
*/
#ifndef ROBO_COORDINATE_H
#define ROBO_COORDINATE_H
class coordinate{
public:
	coordinate(){
		x = 0; y = 0; z = 0;
		theta = 0;
	}
	coordinate(double x_, double y_, double z_, double theta_){
		x = x_; y = y_; z = z_;
		theta = theta_;
	}
//	~coordinate();

	//the coords
	double x;	double y;	double z;
	double theta;
};

#endif
