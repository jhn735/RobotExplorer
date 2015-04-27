#ifndef ROBO_MAP_H
#define ROBO_MAP_H

#include "config.h"
#include "coordinate.h"
	#include <vector>

#ifndef NULL
	#define NULL 0
#endif

class Map{
public:
	Map(const char* mapFilename);
	double distance(coordinate coord1, coordinate coord2);
	coordinate generate_random_coord();
	bool accessible(coordinate coord);	

	void print_section_map();
	void print_region_map();

	//returns true if all regions have been explored
		//for now should only return false
	bool map_explored();	

	//the class prototypes
	class Section;
	
	class Region{
		bool _explored;
		static unsigned next_id;
	 	unsigned _id;
		std::vector<Section *> _section_list;

		public:
		Region();

		bool explored(){ return _explored;};
		void set_explored(){ _explored = true;};
		//what does it do? I wonder.
		void add_section(Section * new_section);
	
		unsigned id(){ return _id;};
	};//end region

	class Section{
		//the corner that has the lowest valued coordinates in the section
		coordinate _corner_meter;
		bool _explorable;
	
		//It's the region that the section belongs to.
		Region * _region;
	
		static double _length_meters;
		static double _width_meters;

		public:	
		/*Section constructors*/
		Section();
		//takes in map, widt&length and the coordinate of the corner pixel.
		Section(unsigned char ** map, 
			unsigned map_w, unsigned map_l, 
			coordinate corner_pixel
		);
		//is the Section explorable?	
		bool explorable(){ return _explorable;};
		//getters and setters for consistency's sake
		Region * region(){ return _region;};
		//returns false if it failed to set region
		bool set_region( Region * new_region);
		//returns true if the coordinate falls within the section
		bool contains_coord(coordinate coord);
		//dimensions in both meters and pixels.
		static double length_meters(){ return _length_meters; };
		static double width_meters(){ return _width_meters; };
	};//end section

private://map's private stash
	static const double pixels_per_meter = MAP_PIXELS_PER_METER;
	
	double _map_length_meters;
	double _map_width_meters;
		//the map should consist of sections
	Section ** _section_map;
		unsigned _section_map_w;
		unsigned _section_map_l;
		//the map should keep track the all the regions in the map
	Region * _region_list;
		unsigned _region_list_size;	
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
		//given the section map, make regions and give those sections regions.
	static void assign_regions(Section ** section_map, unsigned w, unsigned l,
								Region * region_array, unsigned * num_regions);
};

#endif
