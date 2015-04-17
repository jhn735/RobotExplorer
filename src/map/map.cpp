#include "map.h"
#include "lodepng.h"

/* The functions in class Map */
void Map::load_pixel_map(const char * mapFilename, unsigned char ** pixel_map, 
						unsigned * w, unsigned * h){
	lodepng_decode_file(pixel_map, w, h, mapFilename, LCT_GREY, 8);
}

void Map::load_section_map(char ** pixel_map, Map::Section ** section_map){
	
}

Map::Map(const char * mapFilename){
	load_pixel_map(mapFilename,this->pixel_map, &(this->h), &(this->w) );
	load_section_map(this->pixel_map, this->section_map);
}

/* The functions in class Section*/
Map::section::section(){
	
}
