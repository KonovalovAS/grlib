#ifndef CANVAS_HPP_INCLUDED
#define CANVAS_HPP_INCLUDED

#include "color.hpp"
#include "pov.hpp"

#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;

typedef vector<int> v_i;
typedef vector<v_i> matr_i;

class Canvas{
private:

	vector<matr_i> _canvas;

	void convert_vmatri_2_char(char * data);
	void convert_char_2_vmatri(const unsigned char * data);

	bool pov_is_in( const pov& pt );
	void setting_pixel(const pov& pt, color COL);
	pov crd_change( const pov& pt );
public:
	int H,W,C; // height, width, channels;
	
	Canvas(int W_=100, int H_=100, int C_=1, color COL = {255,255,255,255} );
	Canvas(int W_, int H_, int C_, Color_name COLNAME = WHITE );
	
	Canvas(string read_img_name, const int channels);


	void set_pixel(pov pt, color COL);
	void dye_all(color COL);

	void output(string filename);

	friend bool operator == (const Canvas& left, const Canvas& right);
	Canvas& operator = (const Canvas& right);

	friend const Canvas operator + (const Canvas& left, const Canvas& right);

};

	

#endif
