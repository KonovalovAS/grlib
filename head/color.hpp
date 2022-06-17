#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

#include "pov.hpp"

enum Color_name{
	BLACK,
	WHITE,
	RED,
	GREEN,
	BLUE,
};


void get_rgb( Color_name colname, int &R, int &G, int &B );



struct color{
	int r,
	    g,
	    b,
	    alpha;

	color( int R = 255, int G =255, int B = 255, int ALPHA = 255 );
	color( Color_name colname, int ALPHA = 255 );


};



class color_base{
	virtual void get_color( const pov pt, color& COL );
};


class const_color : public color_base{
	// to do
	virtual void get_color( const pov pt, color& COL );
};

class lin_grad : public color_base{
	// to do
	virtual void get_color( const pov pt, color& COL );
};

class rad_grad : public color_base{
	// to do
	virtual void get_color( const pov pt, color& COL );
};





#endif
