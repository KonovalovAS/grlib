#ifndef CANVAS_HPP_INCLUDED
#define CANVAS_HPP_INCLUDED

#include "color.hpp"
#include "pov.hpp"
#include "noise_eliminator.hpp"

#include <vector>
#include <string>

#include "typedefs.hpp"

using std::string;



class Canvas{
private:

	color_matr _canvas;
	
	// is the given point inside the borders? 
	bool pov_is_in( const pov& pt );

	// coordinates transformation
	// (to locate the origin in the lower left corner)
	pov crd_change( const pov& pt );

public:

	int H,W,C; // height, width, channels;
	
	Canvas(int W_=100, int H_=100, int C_=1, color COL = {255,255,255,255} );
	Canvas(string read_img_name, const int channels = 4);

	// working with pixels
	color get_pixel(pov pt_);
	void set_pixel(pov pt, const color COL);
	
	// making all pixels of one color
	void dye_all(const color COL);

	// making all in black-white
	void to_bw();

	// making an image
	// (this method is gonna move to another class "Writer"
	void output(string filename, int channels = -1);

	friend bool operator == (const Canvas& left, const Canvas& right);
	Canvas& operator = (const Canvas& right);

	// adding up two canvases (~images)
	friend const Canvas operator + (const Canvas& left, const Canvas& right);

	// changing the number of color-channels
	// ( shrinking or expanding it )
	bool channels_reconstr( int new_C );


	friend class Noise_eliminator;

};

	

#endif
