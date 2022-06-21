#ifndef CONVERTER_HPP_INCLUDED
#define CONVERTER_HPP_INCLUDED

#include "canvas.hpp"
#include "typedefs.hpp"

// I suppose, this class will be mostly used only in the inside
// procedures of the library, so it won't be available
// to users

class Converter{
public:
	
	static void color_matr_to_chars( const color_matr& cmatr, char * data, int C );

	static void uns_chars_to_color_matr( const unsigned char * data, color_matr& cmatr, int C );

	// In the end, I think it should be only one public function here,
	// which should be a template, like this:
	 
	/*
	template<class FROM_TYPE, class TO_TYPE>
	void Convert( const FROM_TYPE& Origin, TO_TYPE& IMAGE );
	*/

private:

};


#endif
