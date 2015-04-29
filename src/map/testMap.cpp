#include "map.h"
#include "utils.h"
#include <iostream>
using namespace std;
int main(){
	Map map("cave.png");
	Map::Section * s;
	coordinate c;	
	do{
		c = map.generate_random_coord();
		s = map.get_containing_section(c);		
	}while(s == 0);
		c.print();
	cout << "explorable:" << s->explorable();
	map.print_section_map();
return 0;
}
