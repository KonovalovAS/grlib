#include "../head/color.hpp"

#include <cmath>

color::color( int R, int G, int B, int ALPHA ){
	r = R%256;
	g = G%256;
	b = B%256;
	alpha = ALPHA%256;
}

bool operator == (const color& left, const color& right ){
	return     (left.r == right.r)
		&& (left.g == right.g)
		&& (left.b == right.b )
		&& (left.alpha == right.alpha);
}

color& color::operator = (const color& right){
	if( this == &right ){
		return *this;
	}
	r = right.r;
	g = right.g;
	b = right.b;
	alpha = right.alpha;
	return *this;
}

int color::to_bw(){
	return (int) round( (double)(r + g + b)/3 );
}
