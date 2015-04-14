#include "config.h"
#include "coordinate.h"
#include "robot.h"
#include <cmath>
#define CEIL(X) ((int)(X+1))
#ifndef ROBO_MAP_H
#define ROBO_MAP_H

class Map{
private:
static double pixels_per_meter(){ return MAP_PIXELS_PER_METER;};
char ** pixel_map;

public:
	Map();
	Map(const char* mapFilename);
	~Map();

class section{
	coordinate center;
	public:
	
	section();
	~section();
	
	char ** pixel_map;
	
	//dimensions in both meters and pixels. Height may be unnecessary.
	static double length_meters(){ return ceil(Robot::length()); };
	static double length_pixels(){ 
		return length_meters()*Map::pixels_per_meter();};

	static double width_meters(){ return ceil(Robot::width()); };
	static double width_pixels(){ 
		return length_meters()*Map::pixels_per_meter();};

	static double height_meters(){ return ceil(Robot::height());};
	static double height_pixels(){ 
		return height_meters()*Map::pixels_per_meter();};
};

class region{

public:

};	

};

#endif
