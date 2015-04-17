#include "config.h"
#include "coordinate.h"
#include "robot.h"
#include <cmath>

#ifndef ROBO_MAP_H
#define ROBO_MAP_H

class Map{
	static double pixels_per_meter(){ return MAP_PIXELS_PER_METER;};
	//pixel_map stuff
	unsigned char ** pixel_map; 
		unsigned pixel_map_height; unsigned pixel_map_width;
	static void load_pixel_map(const char * mapFilename, 
								char ** pixel_map, 
								unsigned * w, 
								unsigned * h);

	//the map should consist of sections	
	Map::Section ** section_map;
	static void load_section_map(char ** pixel_map, 
								Map::Section ** section_map);  

public:
	Map(const char* mapFilename);
	~Map();


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
	Map::Region * parent_Region;

	//dimensions in both meters and pixels.
	static double length_meters(){ return ceil(Robot::length()); };
	static double length_pixels(){ 
		return length_meters()*Map::pixels_per_meter();};

	static double width_meters(){ return ceil(Robot::width()); };
	static double width_pixels(){ 
		return length_meters()*Map::pixels_per_meter();};

};

class Region{
	bool isExplored;
	static unsigned next_id = 0;
	unsigned id;
public:
	Region(){
		isExplored = false;
		id = next_id;
			next_id++;	
	};

	~Region();
	
	bool explored(){ return isExplored;};
	void setExplore(){ isExplored = true;};
};	

};

#endif
