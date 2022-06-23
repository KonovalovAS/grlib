#include "head/grlib.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(){

	Canvas A("folder/noise_1.png",3);
	cout << "The image is read!" << endl;

	Noise_eliminator NE(10.0f,0.2f,12.0f);
	cout << "Noise eliminator is constructed!" << endl;
	NE(A);
	cout << "Noise is eliminated!" << endl;

	A.output("folder/noise_2.png",3);

	return 0;
}
