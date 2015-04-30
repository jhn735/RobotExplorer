#include "stack.h"
	#include <deque>
	#include <iostream>
using namespace std;
stack::stack(){

};

bool stack::empty(){
	return cont.empty();
};

int stack::size(){
	return cont.size();
};

coordinate stack::top(){
	return cont[0];
};

void stack::push(coordinate c){
	cont.push_front(c);
};

void stack::pop(){
	cont.pop_front();
};

void stack::clear(){
	cont.clear();
};

void stack::print(){
	for(int i = 0; i < cont.size(); i++)
		cont[i].print();		
};


