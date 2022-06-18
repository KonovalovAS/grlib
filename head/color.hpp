#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

#include "pov.hpp"

// just a single color:
struct color{
	int r,
	    g,
	    b,
	    alpha;

	color( int R = 255, int G =255, int B = 255, int ALPHA = 255 );

	friend bool operator == (const color& left, const color& right);
	color& operator = (const color& right);

	int to_bw();

};


/// The ancestor of different types of coloring: 
class color_base{

	// depending on a coloring type, it will calculate a required color-value in any point
	virtual void get_color( const pov pt, color& COL );
};

/// Decsendants:

// constant color:
class const_color : public color_base{

	// just a constant color (the same everywhere)
public:
	color COL;

	// to do
	virtual void get_color( const pov pt, color& COL );
};

// linear gradient:
class lin_grad : public color_base{

	// gradient between COL_1 and COL_2, each of which is located in points node_1 and node_2 (accordingly)
public:
	color COL_1, COL_2;
	pov node_1, node_2;

	// to do
	virtual void get_color( const pov pt, color& COL );
};

// radial gradient:
class rad_grad : public color_base{
	
	// color COL_1 is in the center, but as approaching to the circle of the given Radius
	// changes towards COL_2

public:
	color COL_1, COL_2;
	pov center;
	int Radius;

	// to do
	virtual void get_color( const pov pt, color& COL );
};





#endif
