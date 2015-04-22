#include "map.h"
#include "robot.h"
#include "lodepng.h"
#include "map_utilities.h"
#include <iostream>
#include <cmath>

/************Region Start*****************/
//something for the sections to point when asked what region they belong to.
	//a region should be something that is 
Map::Region::Region(){
	_explored = false;
	_id = next_id;
		next_id++;
};

	//what does it do? I wonder.
void Map::Region::add_section(Section new_section){

	};
	
unsigned Map::Region::next_id = 0;
/*****************Region END*************************/
/***************Section START*********************/
Map::Section::Section(){
	_corner_meter = coordinate(0,0,0,0);
	_explorable = false;
	_region = NULL;
};

	//takes in map, width, length and the coordinate the corner pixel resides.
Map::Section::Section(
	unsigned char ** map, 
	unsigned map_w, unsigned map_l, 
	coordinate corner_pixel

){
	//translate the coordinate from pixels to meters
		double x_meters = corner_pixel.x * pixels_per_meter;
		double y_meters = corner_pixel.y * pixels_per_meter;
	_corner_meter = coordinate(x_meters, y_meters, 0, 0);

	//find the length/width of the section in pixels
	double length_pixels = ceil(_length_meters*pixels_per_meter);
	double width_pixels = ceil(_width_meters*pixels_per_meter);

	//assume the section is non-explorable, innocent until proven guilty
	_explorable = false;

	//for each pixel in the square surrounding section_center
		//if there is an obstacle, the section is indeed non-explorable.
	for(int i = corner_pixel.y; (i < length_pixels) && (i < map_l); i++)
		for(int j = corner_pixel.x; (j < width_pixels) && (j < map_w); j++)
			if(map[i][j] != 0) return;

//if no obstacles are found, the section is explorable
_explorable = true;
};
	
	//returns false if it failed to set region
bool Map::Section::set_region( Region * new_region){
	if(_region != NULL) return false;
	_region = new_region;	
return true;	
};

#define NEAREST 0.5
double Map::Section::_length_meters = ceil_to(NEAREST, Robot::length());
double Map::Section::_width_meters = ceil_to(NEAREST, Robot::width());
/******************Section END***************/

/****************Start Map********************/
/* The functions in class Map */

/*map constructor*/
Map::Map(const char * mapFilename){
	// load the pixel map
	unsigned char * pixel_map;
		unsigned width;
		unsigned length;

	load_pixel_map(mapFilename, pixel_map, &width, &length);
	load_section_map(pixel_map, length, width, 
					_section_map, &_section_map_w, &_section_map_l);
	assign_regions(_section_map, _section_map_w, _section_map_l, 
					_region_list, &_region_list_size);
};

void Map::print_section_map(){
	//for each section in section map
	for(int i = 0; i < _section_map_l; i++){
		for(int j = 0; j < _section_map_w; j++)
			std::cout << _section_map[i][j].explorable();
	std::cout << std::endl; 
	}
};

//this is really just a wrapper function for the lodepng
	//I should probably kill it.
void Map::load_pixel_map(
	const char * mapFilename, 
	unsigned char * pixel_map, 
	unsigned * w, unsigned * l
){
	lodepng_decode_file(&pixel_map, w, l, mapFilename, LCT_GREY, 8);
};

void Map::load_section_map(
	unsigned char * pixel_map_1D, 
	unsigned pixel_w, unsigned pixel_l, 
	Section ** _section_map,
	unsigned * section_w, unsigned * section_l
){
	//translate the 1D pixel_map into a 2D pixel_map
	unsigned char ** pixel_map_2D = 
		alloc_2D_array(pixel_map_1D, pixel_w, pixel_l);

	//calculate the width and length of the _section_map
		double width_pixels = ceil(Section::width_meters()*pixels_per_meter);
	*section_w = width_pixels;

		double length_pixels = ceil(Section::length_meters()*pixels_per_meter);
	*section_l = length_pixels;
	
		//set up the section map and fill it up
	_section_map = new Section*[pixel_l];
	for(int i = 0; i < *section_l; i++){
			//new row in the section map
		_section_map[i] = new Section[pixel_w];
			//the y coordinate of the center
		double corner_y = i*length_pixels;
		
		for(int j = 0; j < *section_w; j++){
				//the x coordinate of the center
			double corner_x = j*width_pixels;
			coordinate corner = coordinate(corner_x, corner_y, 0, 0);
				//set the specified section to be a new section
			_section_map[i][j] = 
				Section(pixel_map_2D, pixel_w, pixel_l, corner);
		}
	}
//deallocate the 2D array made earlier. No need for the raw image.
dealloc_2D_array(pixel_map_2D, pixel_w, pixel_l);
};

//
void Map::assign_regions(
	Section ** section_map, unsigned w, unsigned l,
	Region * region_array, unsigned * num_regions
){
		

};
/***********************End Map*****************/
