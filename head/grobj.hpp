#ifndef GROBJ_HPP_INCLUDED
#define GROBJ_HPP_INCLUDED

#include "canvas.hpp"

#include <vector>
using std::vector;

class grObj_anc{
private:
	color_base * COLOR;
public:

	vector<pov> data;
	
	virtual void rotate( const float angle, const pov origin );
	virtual void draw( Canvas& canv, pov origin );
};







#endif
