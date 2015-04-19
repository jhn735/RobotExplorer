#include "map.h"
#include "robot.h"
#include "lodepng.h"
#include "map_utilities.h"
#include <iostream>
#include <cmath>

/*The functions and variables in class Region */
unsigned Map::Region::next_id = 0;

/* The functions in class Section*/
#define NEAREST 0.5
double Map::Section::_length_meters = ceil_to(NEAREST, Robot::length());
double Map::Section::_length_pixels = 
	ceil(_length_meters*pixels_per_meter);

double Map::Section::_width_meters = ceil_to(NEAREST, Robot::width());
double Map::Section::_width_pixels = 
	ceil(_length_meters*pixels_per_meter);

/*Section constructor*/
Map::Section::Section(unsigned char ** map, 
				unsigned map_w, unsigned map_l, 
				coordinate section_corner
){
	//assume the section is non-explorable, innocent until proven guilty
	_explorable = false;
	_corner = section_corner;

	//for each pixel in the square surrounding section_center
	for(int i = _corner.y; (i < length_pixels()) && (i < map_l); i++){
		for(int j = _corner.x; (j < width_pixels()) && (j < map_w); j++){
		//if there is an obstacle, the section is indeed non-explorable.
			if(map[i][j] != 0) return;
		}
	}
//if no obstacles are found, set the section is explorable
_explorable = true;
}

/* The functions in class Map */
//this is really just a wrapper function for the lodepng
void Map::load_pixel_map(
	const char * mapFilename, 
	unsigned char * pixel_map, 
	unsigned * w, unsigned * l
){
	lodepng_decode_file(&pixel_map, w, l, mapFilename, LCT_GREY, 8);
}


void Map::load_section_map(
	unsigned char * pixel_map_1D, 
	unsigned w, unsigned l, 
	Section ** section_map,
	unsigned * section_w, unsigned * section_l
){
	//translate the 1D pixel_map into a 2D pixel_map
	unsigned char ** pixel_map_2D = alloc_2D_array(pixel_map_1D, w, l);
	//calculate the width and length of the section_map
	*section_w = w/Section::width_pixels();
	*section_l = l/Section::length_pixels();
	
	//set up the section map and fill it up
	section_map = new Section*[l];
	for(int i = 0; i < *section_l; i++){
		//new row in the section map
		section_map[i] = new Section[l];

		//the y coordinate of the center
		double corner_y = i*Section::length_pixels();
		
		for(int j = 0; j < *section_w; j++){
			//the x coordinate of the center
			double corner_x = j*Section::width_pixels();
			coordinate corner = coordinate(corner_x, corner_y, 0, 0);
			
			//set the specified section to be a new section
			section_map[i][j] =	Section(pixel_map_2D, w, l, corner);
		}
	}
//deallocate the 2D array made earlier
dealloc_2D_array(pixel_map_2D, w, l);
}

/*map constructor*/
Map::Map(const char * mapFilename){
	// load the pixel map
	unsigned char * pixel_map;
		unsigned width;
		unsigned length;

	load_pixel_map(mapFilename, pixel_map, &width, &length);
	load_section_map(pixel_map, length, width, 
					section_map, &_section_map_w, &_section_map_l);
}
