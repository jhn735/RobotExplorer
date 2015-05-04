#include "map.h"
#include "config.h"
#include "lodepng.h"
#include "utils.h"
	#include <iostream>
	#include <vector>
	#include <cmath>
	#include <ctime>
	#include <cstdlib>

/***************Section START*********************/
Map::Section::Section(){
	_corner_meter = coordinate(0,0,0,0);
	_explorable = false;
	_explored = false;
};

	//takes in map, width, length and the coordinate the corner pixel resides.
Map::Section::Section(
	unsigned char ** map, 
	unsigned map_w, unsigned map_l, 
	coordinate corner_pixel

){
	//translate the coordinate from pixels to meters
		double x_meters = corner_pixel.x / pixels_per_meter;
		double y_meters = corner_pixel.y / pixels_per_meter;
	_corner_meter = coordinate(x_meters, y_meters, 0, 0);

		y_meters += _length_meters/2;
		x_meters += _width_meters/2;
	_center_meter = coordinate(x_meters, y_meters, 0, 0);
	//find the length/width of the section in pixels
	double length_pixels = ceil(_length_meters*pixels_per_meter);
	double width_pixels = ceil(_width_meters*pixels_per_meter);

	//assume the section is non-explorable, innocent until proven guilty
	_explorable = false;

	//if the section's boundaries extend past the image's boundaries
		double section_y_upper = corner_pixel.y+length_pixels;
	if(corner_pixel.y < 0 || section_y_upper > map_l) return;
		
		double section_x_upper = corner_pixel.x+width_pixels;
	if(corner_pixel.x < 0 || section_x_upper > map_w) return;

	//for each pixel in the square surrounding section_center
		//if there is an obstacle, the section is indeed non-explorable.
	for(int i = corner_pixel.y; (i < section_y_upper); i++)
		for(int j = corner_pixel.x; (j < section_x_upper); j++)
			if(map[i][j] != 255) return;
	
	//if all goes well the section is explorable
	_explorable = true;
};

bool Map::Section::explorable(){ return _explorable;};

bool Map::Section::explored(){
	if(!_explorable) return true;
return _explored;
};	

void Map::Section::set_explored(){ _explored = true;};

bool Map::Section::contains_coord(coordinate coord){
	double range_x_lower = _corner_meter.x; 
	double range_x_higher = range_x_lower + width_meters();
	if(coord.x <= range_x_lower || coord.x > range_x_higher)
		return false;

	double range_y_lower = _corner_meter.y;
	double range_y_higher = range_y_lower + length_meters();
	if(coord.y <= range_y_lower || coord.y > range_y_higher)
		return false;
return true;
};

//it is best to tune NEAREST to produce the smallest map but also so that
	//it doesn't produce extreme false positives 0.5 and 1 seem to work
#define NEAREST 1
double Map::Section::_length_meters = ceil_to(NEAREST, ROBOT_LENGTH_METERS);
	double Map::Section::width_meters(){ return _width_meters;};
double Map::Section::_width_meters = ceil_to(NEAREST, ROBOT_HEIGHT_METERS);
	double Map::Section::length_meters(){ return _length_meters;};
/******************Section END***************/

/****************Start Map********************/
/* The functions in class Map */
int Map::random_seed = 0;

/*map constructor*/
Map::Map(const char * mapFilename){
	// load the pixel map
	unsigned char * pixel_map = NULL;
		unsigned width = 0;
		unsigned length = 0;
	load_pixel_map(mapFilename, pixel_map, width, length);
	//set the map's length and width in meters
		_map_length_meters = (double)(length/pixels_per_meter);
		_map_width_meters = (double)(width/pixels_per_meter);
	load_section_map(pixel_map, length, width, 
					_section_map, _section_map_w, _section_map_l);
};


//this is really just a wrapper function for the lodepng
	//I should probably kill it.
void Map::load_pixel_map(
	const char * mapFilename, 
	unsigned char * &pixel_map, 
	unsigned &w, unsigned &l
){
	//for the sake of safty I'm using the function that returns an error
	std::vector<unsigned char> image;
	unsigned error = lodepng::decode(image, w, l, mapFilename, LCT_GREY);
	if(error != 0) 
		std::cout << "error " << lodepng_error_text(error) << std::endl;
	//set the pixel map to be the value that the vector holds
	pixel_map = &image[0];	
};

void Map::load_section_map(
	unsigned char * pixel_map_1D, 
	unsigned pixel_w, unsigned pixel_l, 
	Section ** &_section_map,
	unsigned &section_w, unsigned &section_l
){
	//translate the 1D pixel_map into a 2D pixel_map
	unsigned char ** pixel_map_2D = 
		alloc_2D_array(pixel_map_1D, pixel_w, pixel_l);

	//calculate the width and length of the _section_map
		double width_pixels = ceil(Section::width_meters()*pixels_per_meter);
	section_w = ceil(pixel_w/width_pixels);

		double length_pixels = ceil(Section::length_meters()*pixels_per_meter);
	section_l = ceil(pixel_l/length_pixels);
	
		//set up the section map and fill it up
	_section_map = new Section*[section_l];
	for(int i = 0; i < section_l; i++){
			//new row in the section map
		_section_map[i] = new Section[section_w];
			//the y coordinate of the center
		double corner_y = i*length_pixels;
		
		for(int j = 0; j < section_w; j++){
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

//returns a random coordinate whose section is unexplored.
coordinate Map::generate_random_coord(){
	if(map_explored()) return coordinate(0,0,0,0);

	//generate a random number between 1 and 100 
	double rand = rand_between(1, 100, random_seed);
		random_seed++;
	//if the section is explorable() and isn't explored
		//if rand is <= 0 return the center coordinate
	while(true){
	  for(int i = 0; i < _section_map_l; i++)
		for(int j = 0; j < _section_map_l; j++){
			Section s = _section_map[i][j];
			if(s.explorable() && !s.explored())
				if(rand > 0) rand--;
				else return s._center_meter;	
		}//end for(int j...	
	};//end while
};

//prints out a map of traversible and non-traversible sections
void Map::print_section_map(){
	//for each section in section map
	for(int i = 0; i < _section_map_l; i++){
		for(int j = 0; j < _section_map_w; j++){
			Section s = _section_map[i][j];
			std::cout << s.explorable();
		}
		std::cout << std::endl; 
	}
};

Map::Section * Map::get_containing_section(coordinate coord){
	//get a ball park estimate of which sections the cord may be in.
	int est_i =(int) (coord.x/Section::width_meters());
	int est_j =(int) (coord.y/Section::length_meters());
	int range = 2;

	int i_lower = (est_i-range>0)?(est_i-range):0;
	int i_upper = (est_i+range<_section_map_l)?(est_i+range):_section_map_l-1;

	int j_lower = (est_j-range>0)?(est_j-range):0;
	int j_upper = (est_j+range<_section_map_w)?(est_j+range):_section_map_w-1;

	//for each section in the range
		//if the section contains the coordinate and it is explorable
			//return true		
	for(int i = i_lower; i <= i_upper; i++){
		for(int j = j_lower; j <= j_upper; j++){
			Section s = _section_map[i][j];
			if(s.contains_coord(coord)) return &_section_map[i][j];
		}}
	//if it hasn't been found search through all of them
	for(int i = 0; i < _section_map_l; i++)
		for(int j = 0; j < _section_map_w; j++){
			Section s = _section_map[i][j];
			if(s.contains_coord(coord)) return &_section_map[i][j]; 
		}
//if all else fails return null
return NULL;	
};

bool Map::accessible(coordinate coord){
	Section * s = get_containing_section(coord);
	if(s == NULL) return false;
return s->explorable();
};

void Map::mark_explored(coordinate coord){
	Section * s = get_containing_section(coord);
	if(s == NULL) return;
	s->set_explored();
};

bool Map::map_explored(){
	//for each section in section map
		//if the section has not been explored return false
	for(int i = 0; i < _section_map_l; i++)
		for(int j = 0; j < _section_map_w; j++)
			if(!_section_map[i][j].explored()) return false;	
//if all else fails the map has been explored
return true;
};
/***********************End Map*****************/

