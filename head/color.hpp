#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED


enum Color_name{
	BLACK,
	WHITE,
	RED,
	GREEN,
	BLUE,
};


struct color{
	int r,
	    g,
	    b,
	    alpha;

	color( int R = 255, int G =255, int B = 255, int ALPHA = 255 );
	color( Color_name colname, int ALPHA = 255 );

};


void get_rgb( Color_name colname, int &R, int &G, int &B );


#endif
