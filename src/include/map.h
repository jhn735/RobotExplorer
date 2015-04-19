#include "config.h"
#include "coordinate.h"
#include "robot.h"
#include <iostream>
#include <cmath>
#ifndef NULL
	#define NULL 
#endif

#ifndef ROBO_MAP_H
#define ROBO_MAP_H

class Map{
public:
	Map(const char* mapFilename);
	//~Map();
	
//something for the sections to point when asked what region they belong to.
class Region{
	bool _explored;
	static unsigned next_id;
	unsigned _id;
public:
	Region(){
		_explored = false;
		_id = next_id;
			next_id++;	
	};

	//~Region();
	
	bool explored(){ return _explored;};
	void set_explored(){ _explored = true;};
	
	unsigned id(){ return _id;};
};

//Section is a 2D flat piece of the map.
class Section{
	//the corner that has the lowest valued coordinates in the section
	coordinate _corner;
	bool _explorable;
	
	//It's the region that the section belongs to.
	Region * _region;
	
	static double _length_meters;
	static double _length_pixels;
	
	static double _width_meters;
	static double _width_pixels;

	public:	
	Section(){ 
		_corner = coordinate(0,0,0,0);
		_explorable = false;
		_region = NULL;
	};
	
	Section(unsigned char ** map, unsigned map_w, 
			unsigned map_l, coordinate section_corner);
	//~Section();
	
	//is the Section explorable? has it been explored?	
	bool explorable(){ return _explorable;};

	//getters and setters for consistency's sake
	Region * region(){ return _region;};
	void set_region( Region * new_region){_region = new_region;};

	//dimensions in both meters and pixels.
	static double length_meters(){ return _length_meters; };
	static double length_pixels(){ return _length_pixels; };

	static double width_meters(){ return _width_meters; };
	static double width_pixels(){ return _width_pixels; };

};
private:
	static const double pixels_per_meter = MAP_PIXELS_PER_METER;
	
	//pixel_map stuff
	static void load_pixel_map(const char * mapFilename, 
								unsigned char * pixel_map, 
								unsigned * w, 
								unsigned * l);

	//the map should consist of sections	
	Section ** section_map;
		unsigned _section_map_w;
		unsigned _section_map_l;
	static void load_section_map(unsigned char * pixel_map_1D,
								unsigned w, unsigned l, 
								Section ** section_map,
								unsigned * section_w, unsigned * section_l);  
};

#endif
