#ifndef ROBO_MAP_H
#define ROBO_MAP_H

#include "config.h"
#include "coordinate.h"

#ifndef NULL
	#define NULL 0
#endif

class Map{
public:
	Map(const char* mapFilename);
	coordinate generate_random_coord();

	void print_section_map();
	bool accessible(coordinate coord);	
	void mark_explored(coordinate coord);
	//returns true if all regions have been explored
		//for now should only return false
	bool map_explored();	

	class Section{
		//the corner that has the lowest valued coordinates in the section
		coordinate _corner_meter;
		bool _explorable;
		bool _explored;	
	
		static double _length_meters;
		static double _width_meters;

		public:	
		coordinate _center_meter;
		/*Section constructors*/
		Section();
		//takes in map, widt&length and the coordinate of the corner pixel.
		Section(unsigned char ** map, 
			unsigned map_w, unsigned map_l, 
			coordinate corner_pixel
		);
		//is the Section explorable?	
		bool explorable();

		bool explored();
		void set_explored();
		//returns true if the coordinate falls within the section
		bool contains_coord(coordinate coord);
		//dimensions in both meters and pixels.
		static double length_meters();
		static double width_meters();
	};//end section

private://map's private stash
	static const double pixels_per_meter = MAP_PIXELS_PER_METER;
	static int random_seed;	
	double _map_length_meters;
	double _map_width_meters;
		//the map should consist of sections
	Section ** _section_map;
		unsigned _section_map_w;
		unsigned _section_map_l;
	Section * get_containing_section(coordinate coord);
		//the load map function they do what their name suggests
			//load the image from file
	static void load_pixel_map(const char * mapFilename, 
								unsigned char * &pixel_map, 
								unsigned &w, 
								unsigned &l);
		//given the image, create a map of sections that are (non)explorable
	static void load_section_map(unsigned char * pixel_map_1D,
								unsigned w, unsigned l, 
								Section ** &section_map,
								unsigned &section_w, unsigned &section_l);
};

#endif
