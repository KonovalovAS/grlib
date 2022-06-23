#ifndef WRITER_HPP_INCLUDED
#define WRITER_HPP_INCLUDED

#include "converter.hpp" // converter includes canvas and color
#include "canvas.hpp"

// Eventually this should be a universal writer
// for all available image formats
// that stb-library provides

enum IMG_TYPE{
	PNG,
	JPEG,
	BMP,
	GIF,
};

class Writer{
public:
	static void Output_PNG( const Canvas& CNV );

	// The final goal: single public function:
	static void write_image( const Canvas& CNV, IMG_TYPE = PNG );
	
};

#endif
