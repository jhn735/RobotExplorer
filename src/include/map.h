#include "config.h"
#include "coordinate.h"
#include "robot.h"
#include <cmath>
#define NULL 0

#ifndef ROBO_MAP_H
#define ROBO_MAP_H

class Map{
public:
	Map(const char* mapFilename);
	~Map();
	
//something for the sections to point when asked what region they belong to.	
class Region{
	bool isExplored;
	static unsigned * next_id;
	unsigned id;
public:
	Region(){
		isExplored = false;
		id = *next_id;
			(*next_id)++;	
	};

	~Region();
	
	bool explored(){ return isExplored;};
	void setExplored(){ isExplored = true;};
};

//Section is a 2D flat piece of the map.
class Section{
	coordinate center;
	bool isExplorable;

	public:	
	Section(){ 
		center = coordinate(0,0,0,0);
		isExplorable = false;
		parent_Region = NULL;
	};
	
	Section(char ** map, coordinate Section_center);
	~Section();
	
	//is the Section explorable? has it been explored?	
	bool explorable(){return isExplorable;};
	
	//I call it parent_Region for no real reason
	//it's the region that the section belongs to.
	Region * parent_Region;

	//dimensions in both meters and pixels.
	static double length_meters(){ return ceil(Robot::length()); };
	static double length_pixels(){ 
		return length_meters()*Map::pixels_per_meter();};

	static double width_meters(){ return ceil(Robot::width()); };
	static double width_pixels(){ 
		return length_meters()*Map::pixels_per_meter();};

};



private:
	static double pixels_per_meter(){ return MAP_PIXELS_PER_METER;};
	
	//pixel_map stuff
	static void load_pixel_map(const char * mapFilename, 
								unsigned char ** pixel_map, 
								unsigned * w, 
								unsigned * h);

	//the map should consist of sections	
	Section ** section_map;
	static void load_section_map(unsigned char ** pixel_map, 
								Section ** section_map);  
	//region_next_id
	static unsigned * region_next_id;
	

};

#endif
