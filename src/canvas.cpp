#include "../head/canvas.hpp"

Canvas::Canvas(int H_, int W_, int C_){
	H = H_;
	W = W_;
	C = C_;

	_canvas = vector<matr_i> (C,
				  vector<v_i> (H, 
					       vector<int> (W,255) ) );
}

Canvas::Canvas(string& filename){
	int channels = 3;
	unsigned char * data = stbi_load(filename.c_str(),&W,&H,&C,channels);
	_canvas = vector<matr_i> (C,
				  vector<v_i> (H,
					       vector<int> (W,255) ) );
	convert_char_2_vmatri(data);
}

void Canvas::convert_char_2_vmatri(const unsigned char * data){
	try{
		for(int ch=0; ch<C; ch++)
			for(int row=0; row<H; row++)
				for(int col=0; col<W; col++)
					_canvas[ch][row][col] = (int)data[ ch + (col*C) + (row*W*C) ];
	}
	catch(...){
		std::cout << "Something went wrong!!\n";
	}
}

/*
// Copied from my old work as a reference:
void Reading::Read_the_image(Vint& New_image, std::string filename){
    int H,W,CHANNELS;
    unsigned char *data = stbi_load(filename.c_str(),&W,&H,&CHANNELS,3);
    Vint Image (H,vvint(W,vint(CHANNELS)));
    convert_char_to_Vint( data, Image );
    New_image = Image;
}

*/

void Canvas::output(string& filename){
	char data[H*W*C];
	convert_vmatri_2_char(data);
	stbi_write_png(filename.c_str(),W,H,C,data,W*C);
}

void Canvas::convert_vmatri_2_char(char * data){
	try{
		for(int ch=0; ch<C; ch++)
			for(int row=0; row<H; row++)
				for(int col=0; col<W; col++)
					data[ ch + (col*C) + (row*W*C) ] = (char)(_canvas[ch][row][col]);
	}
	catch(...){
		std::cout << "Something went wrong!";
	}
}
