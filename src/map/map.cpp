#include "map.h"
#include "lodepng.h"

/* The functions in class Map */
void Map::load_pixel_map(const char * mapFilename, unsigned char ** pixel_map, 
						unsigned * w, unsigned * h){
	lodepng_decode_file(pixel_map, w, h, mapFilename, LCT_GREY, 8);
}

void Map::load_section_map(unsigned char ** pixel_map, Map::Section ** section_map){
	
}

Map::Map(const char * mapFilename){
	//set all the variables to their initial values
	region_next_id = new unsigned;
		*region_next_id = 0;

	// load the pixel map
	unsigned char ** pixel_map;
		unsigned pixel_map_height;
		unsigned pixel_map_width;
	load_pixel_map(mapFilename, pixel_map, &pixel_map_height, &pixel_map_width);
	load_section_map(pixel_map, this->section_map);
}

/* The functions in class Section*/

