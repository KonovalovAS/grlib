#include "head/grlib.hpp"

int main(){

	int C(4);
	int H(254), W(254);
	Canvas Canv(H,W,C,WHITE);
	
	for(int y=0; y<H; y++){
		for(int x=0; x<W; x++){
			int alpha = (x > 2*y)? 70 : 150;
			if( 2*x < y ) alpha = 230;
			Canv.set_pixel( {x,y}, {x,y,x,alpha} );
		}
	}
	Canv.output("folder/test5.png");
	
	return 0;
}
