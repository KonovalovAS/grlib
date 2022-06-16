#ifndef CANVAS_HPP_INCLUDED
#define CANVAS_HPP_INCLUDED

#include <vector>
#include <string>
#include <iostream>


using std::vector;
using std::string;

typedef vector<int> v_i;
typedef vector<v_i> matr_i;

class Canvas{
private:

	vector<matr_i> _canvas;

	void convert_vmatri_2_char(char * data);
	void convert_char_2_vmatri(const unsigned char * data);
public:
	int H,W,C; // height, width, channels;
	
	Canvas(int W_=100, int H_=100, int C_=1);
	Canvas(string& img_toread_name);

	void output(string filename);
};






#endif
