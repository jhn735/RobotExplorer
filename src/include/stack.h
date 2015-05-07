#include "coordinate.h"
	#include <deque>

//to help with the debug
	//should be interchangable with stack
	//except a print function
class stack{
	std::deque<coordinate> cont;
public:
	stack();
	bool empty();
	bool contains(coordinate c);
	int size();
	coordinate top();
	void push(coordinate c);
	void pop();
	void clear();
	void print();


};
