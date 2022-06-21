#include "../head/color.hpp"

#include <cmath>
#include <algorithm>

color::color( int R, int G, int B, int ALPHA ){
	r = R%256;
	g = G%256;
	b = B%256;
	alpha = ALPHA%256;
}

color operator + (const color& left, const color& right){
	int r = (int) ( (
		  round( (float)( (left.alpha) *(left.r) ) )
		+ round( (float)( (right.alpha)*(right.r) ) )
		) / 255 );
	int g = (int) ( (
		  round( (float)( (left.alpha) *(left.g) ) )
		+ round( (float)( (right.alpha)*(right.g) ) )
		) / 255 );
	int b = (int) ( (
		  round( (float)( (left.alpha) *(left.b ) ) )
		+ round( (float)( (right.alpha)*(right.b) ) )
		) / 255 );
	int alpha = (int) ( (
		  round( (float)( (left.alpha) *(left.alpha) ) )
		+ round( (float)( (right.alpha)*(right.alpha) ) )
		) / 255 );

	color newcol = {
			std::min( r, 255 ),
			std::min( g, 255 ),
			std::min( b, 255 ),
			std::min( alpha, 255 )
		};
	return newcol;
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

void color::mk_bw(){
	int bw = this->to_bw();
	r = bw;
	g = bw;
	b = bw;
}
