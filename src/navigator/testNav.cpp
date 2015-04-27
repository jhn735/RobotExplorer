#include "navigator.h"
#include "coordinate.h"
	#include <iostream>
using namespace std;

int main(){
	coordinate a(1,2,3,4);
	coordinate b(1,2,3,4);
	cout << (a == b) << endl;
	b = coordinate(1,2,4,3);
	cout << (a == b) << endl;
return 0;
};
