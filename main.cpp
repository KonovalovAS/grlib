#include "head/grlib.hpp"

int main(){

	int C(4);
	int H(254), W(254);
	Canvas Canv(H,W,C);
	
	for(int y=0; y<H; y++){
		for(int x=0; x<W; x++){
			int alpha = (x < y)? 254 : 180;
			if( W-x < y ) alpha = round( (float)alpha/2 );
			Canv.set_pixel( {x,y}, {y,x,H-y,alpha} );
		}
	}
	Canv.output("folder/test6.png");
	
	return 0;
}
