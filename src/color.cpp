#include "../head/color.hpp"

color::color( int R, int G, int B, int ALPHA ){
	r = R%256;
	g = G%256;
	b = B%256;
	alpha = ALPHA%256;
}

color::color( Color_name colname, int ALPHA ){
	get_rgb( colname, r,g,b );
	alpha = ALPHA;
}

void get_rgb( Color_name colname, int &R, int &G, int &B ){
	switch( colname ){
	case RED:
		R = 255;
		G = 0;
		B = 0;
		break;
	case GREEN:
		R = 0;
		G = 255;
		B = 0;
		break;
	case BLUE:
		R = 0;
		G = 0;
		B = 255;
		break;
	case BLACK:
		R = 0;
		G = 0;
		B = 0;
		break;
	case WHITE:
		R = 255;
		G = 255;
		B = 255;
		break;
	}
}

