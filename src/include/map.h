#include "config.h"
#include "coordinate.h"
#include "robot.h"
#include <cmath>
#ifndef ROBO_MAP_H
#define ROBO_MAP_H

class Map{
private:
static const double pixels_per_meter = MAP_PIXELS_PER_METERS;

public:
	Map();
	Map(const char* mapFilename);
	~Map();

static class section{
	coordinate center;
	public:
	section();
	~section();
	
	static const double length = ceil(Robot::length);
	static const double width = ceil(Robot::width);
	static const double height = ceil(Robot::height);
};

static class region{

public:

};	

};

#endif
