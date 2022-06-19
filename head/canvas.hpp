#ifndef CANVAS_HPP_INCLUDED
#define CANVAS_HPP_INCLUDED

#include "color.hpp"
#include "pov.hpp"

#include <vector>
#include <string>

using std::vector;
using std::string;

typedef vector<color> col_vec;
typedef vector<col_vec> col_matr;

class Canvas{
private:

	col_matr _canvas;

	void convert_colmatr_2_char(char * data);
	
	void conv_2char_1( char * data );
	void conv_2char_2( char * data );
	void conv_2char_3( char * data );
	void conv_2char_4( char * data );

	void convert_char_2_colmatr(const unsigned char * data);

	void conv_2colmatr_1( const unsigned char * data );
	void conv_2colmatr_2( const unsigned char * data );
	void conv_2colmatr_3( const unsigned char * data );
	void conv_2colmatr_4( const unsigned char * data );

	bool pov_is_in( const pov& pt );
	pov crd_change( const pov& pt );
public:
	int H,W,C; // height, width, channels;
	
	Canvas(int W_=100, int H_=100, int C_=1, color COL = {255,255,255,255} );
	
	Canvas(string read_img_name, const int channels = 4);

	color get_pixel(pov pt_);
	void set_pixel(pov pt, const color COL);
	void dye_all(const color COL);

	void output(string filename);

	friend bool operator == (const Canvas& left, const Canvas& right);
	Canvas& operator = (const Canvas& right);

	friend const Canvas operator + (const Canvas& left, const Canvas& right);

};

	

#endif
