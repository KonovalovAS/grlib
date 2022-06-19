#include "head/grlib.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(){

	Canvas A(500,500,4,{255,255,255,0});
	Canvas B(500,500,4,{255,255,255,0});
	
	for(int y=0; y<200; y++)
		for(int x=0; x<200; x++){
			A.set_pixel( {100+x,100+y}, {255,0,0,200} );
			B.set_pixel( {200+x,200+y}, {0,0,255,200} );
		}
	
	cout << "A & B are drawn" << endl;

	Canvas C = A + B;
	
	A.output("folder/test1_a.png");
	B.output("folder/test1_b.png");

	C.output("folder/test1_c_equal_a_plus_b.png");

	return 0;
}
