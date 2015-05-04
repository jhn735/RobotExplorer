#ifndef ROBO_MAP_UTILITIES
#define ROBO_MAP_UTILITIES

//round value to nearest
double round_to( double nearest, double value);

//round value up to the nearest
	//does the same thing as round_to only skips the dec check
double ceil_to( double nearest, double value);

double rand_between(double lower, double upper, int seed);

//allocate a 2D array given the 1D array, width, and height
unsigned char ** alloc_2D_array(unsigned char * arr, unsigned w, unsigned h);

//display 2D array given array, height and width
void disp(unsigned char ** a, unsigned w, unsigned h);

void disp(unsigned char * a, unsigned w, unsigned h);

void dealloc_2D_array(unsigned char ** arr, unsigned w, unsigned h);

void wait_iterations(int num_iterations);
#endif
