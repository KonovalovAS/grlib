#ifndef CONVERTER_HPP_INCLUDED
#define CONVERTER_HPP_INCLUDED

#include "canvas.hpp"


class Converter{
public:
	
	static void Canvas_2_char( const Canvas& CNV, char * data );
	static void unsigned_char_2_Canvas( const unsigned char * data, Canvas& CNV );

	// After all, here should be only one public function,
	// which will be a template, like this:
	 
	/*
	template<class FROM_TYPE, class TO_TYPE>
	void Convert( const FROM_TYPE& Origin, TO_TYPE& IMAGE );
	*/

};


#endif
