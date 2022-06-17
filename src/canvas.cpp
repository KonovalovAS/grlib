#include "../head/canvas.hpp"

#define STB_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#include <iostream>

Canvas::Canvas(int H_, int W_, int C_, color COL ){
	H = H_;
	W = W_;
	C = C_;

	_canvas = vector<matr_i> (C,
				  vector<v_i> (H, 
					       vector<int> (W,255) ) );
	dye_all( COL );
}

Canvas::Canvas(int H_, int W_, int C_, Color_name COLNAME ){
	H = H_;
	W = W_;
	C = C_;

	_canvas = vector<matr_i> (C,
				  vector<v_i> (H, 
					       vector<int> (W,255) ) );
	color COL( COLNAME );
	dye_all( COL );
}


Canvas::Canvas(string read_img_name,const int channels){
	unsigned char * data = stbi_load(read_img_name.c_str(),&W,&H,&C,channels);
	_canvas = vector<matr_i> (C,
				  vector<v_i> (H,
					       vector<int> (W,255) ) );
	convert_char_2_vmatri(data);
}


pov Canvas::crd_change( const pov& pt ){
	return { pt.x, (H-1)-pt.y };

}

bool Canvas::pov_is_in( const pov& pt ){
	return ( 0 <= pt.x ) && (pt.x <= W-1 )
	    && ( 0 <= pt.y ) && (pt.y <= H-1 );
}

void Canvas::set_pixel(pov pt_, color COL){
	
	pov pt = crd_change( pt_ );
	
	if( pov_is_in( pt ) ){
		try{
			setting_pixel(pt,COL);
		}
		catch(...){
			std::cout << "Couldn't set pixel (" << pt.x << "," << pt.y << ")\n";
		}
	}
}

void Canvas::setting_pixel(const pov& pt, color COL){
	switch( C ){
	case 1:
		_canvas[0][pt.y][pt.x] = round( (double)( COL.r + COL.g + COL.b )/3 );
		break;
	case 2:
		_canvas[0][pt.y][pt.x] = round( (double)( COL.r + COL.g + COL.b )/3 );
		_canvas[1][pt.y][pt.x] = COL.alpha;
		break;
	case 3:
		_canvas[0][pt.y][pt.x] = COL.r; 
		_canvas[1][pt.y][pt.x] = COL.g; 
		_canvas[2][pt.y][pt.x] = COL.b; 
		break;
	case 4: 
		_canvas[0][pt.y][pt.x] = COL.r; 
		_canvas[1][pt.y][pt.x] = COL.g; 
		_canvas[2][pt.y][pt.x] = COL.b;
		_canvas[3][pt.y][pt.x] = COL.alpha;
		break;
	}

}

void Canvas::dye_all( color COL ){
	
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			switch( C ){
			case 1:
				_canvas[0][i][j] = round( (double)( COL.r + COL.g + COL.b )/3 );
				break;
			case 2:

				_canvas[0][i][j] = round( (double)( COL.r + COL.g + COL.b )/3 );
				_canvas[1][i][j] = COL.alpha;
				break;
			case 3:
				_canvas[0][i][j] = COL.r; 
				_canvas[1][i][j] = COL.g; 
				_canvas[2][i][j] = COL.b; 
				break;
			case 4: 
				_canvas[0][i][j] = COL.r; 
				_canvas[1][i][j] = COL.g; 
				_canvas[2][i][j] = COL.b;
				_canvas[3][i][j] = COL.alpha;
				break;
			}
		}
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


void Canvas::output(string filename){
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
