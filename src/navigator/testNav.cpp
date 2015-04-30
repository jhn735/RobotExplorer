#include "navigator.h"
#include "coordinate.h"
	#include <iostream>
using namespace std;

int main(){
Map map("cave.png");
	coordinate c(0,0,0,0);
	Navigator nav(&map, c);


//build the tree
for(int i = 0; i < 100; i++){
	c = nav.next_waypoint(c);
		//cout << endl << "coord: ";
		//c.print();
		cout << endl << "-----------" << endl;
		cout << "tree: " << endl;
		nav.print_tree();
	
}
	cout << endl;
	nav.plan_path_to_goal(nav.next_goal());
	
return 0;
};
