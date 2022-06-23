#ifndef CONVERTER_HPP_INCLUDED
#define CONVERTER_HPP_INCLUDED

#include "typedefs.hpp"

// I suppose, this class will be mostly used only in the inside
// procedures of the library, so it won't be available
// to users

class Converter{
public:

	// for methods of Canvas:
	static void color_matr_to_chars( const color_matr& cmatr, char * data, int C );
	static void uns_chars_to_color_matr( const unsigned char * data, color_matr& cmatr, int C );

	// for methods of Noise_eliminator:
	static void color_matr_to_float_matr_layers( const color_matr& cmatr, vector<float_matr>& data, int C, int border );
	static void float_matr_layers_to_color_matr( const vector<float_matr>& data, color_matr& cmat );

	// In the end, I think it should be only one public function here,
	// which should be a template, like this:
	 
	/*
	template<class FROM_TYPE, class TO_TYPE>
	void Convert( const FROM_TYPE& Origin, TO_TYPE& IMAGE );
	*/

private:

};


#endif
