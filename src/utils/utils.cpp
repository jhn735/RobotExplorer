#include "utils.h"
	#include <cmath>
	#include <iostream>
	#include <cstdlib>
using namespace std;
//round value to nearest
double round_to( double nearest, double value){
	//get the factor of value and nearest
		//this gives the amount of 'nearest' units
		//and how close the value is to the next one.
	double val = value/nearest;
	//separate the number of 'nearest' units and decimal left over
	double units = floor(val);
	double dec = val - units;
	//return product of units and nearest or (units+1) and nearest depending.
	if(dec < 0.5) return units*nearest;

return (units+1)*nearest;	
};

//round value up to the nearest
	//does the same thing as round_to only skips the dec check
double ceil_to( double nearest, double value){
	double val = value/nearest;
	double units = ceil(val);
return units*nearest;
};

double rand_between(double lower, double upper, int seed){
	int range = upper - lower;
	srand(time(NULL)+seed);
	int randNum = (rand()%(int)range)+(int)lower;
return (double)randNum; 
};

//allocate a 2D array given the 1D array, width, and height
unsigned char ** alloc_2D_array(unsigned char * arr, unsigned w, unsigned h){
	unsigned char ** retVal = new unsigned char*[h];
	int arr_index = 0;
	for(unsigned i = 0; i < h; i++){
		//create a new row
		retVal[i] = new unsigned char[w];
		for(unsigned j = 0; j < w; j++){
/*			std::cout << "i:" << i
					  << " j:" << j
					  << " arr_index:" << arr_index
					  << std::endl;
*/			retVal[i][j] = arr[arr_index];
			arr_index++;
		}
	}
	return retVal;
};

//display 2D array given array, height and width
void disp(unsigned char ** a, unsigned w, unsigned h){
	for(unsigned i = 0; i < h; i++){
		for(unsigned j = 0; j < w; j++){
			std::cout << (int)a[i][j];
		}
		std::cout << std::endl;
	}
};

void disp(unsigned char * a, unsigned w, unsigned h){
	int arr_index = 0;
	for(unsigned i = 0; i < h; i++){
		for(unsigned j = 0; j < w; j++){
			std::cout << (unsigned)(a[arr_index]) << ' ';
			arr_index++;
		}
		std::cout << "endl" << std::endl << std::endl;
	}
};	

void dealloc_2D_array(unsigned char ** arr, unsigned w, unsigned h){
	for(unsigned i = 0; i < h; i++){
		delete arr[i];
	}
	delete arr;
};

void wait_iterations(int num_iterations){
	for(unsigned i = num_iterations; i>0; i--){}
};
