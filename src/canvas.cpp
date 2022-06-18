#include "../head/canvas.hpp"

#define STB_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#include <iostream>

// CONSTRUCTORS

Canvas::Canvas(int H_, int W_, int C_, color COL ){
	H = H_;
	W = W_;
	C = C_;

	_canvas = col_matr( H, col_vec( W, COL ) );

	dye_all( COL );
}

Canvas::Canvas(string read_img_name,const int channels){
	unsigned char * data = stbi_load(read_img_name.c_str(),&W,&H,&C,channels);
	_canvas = col_matr( H, col_vec( W, {255,255,255,255} ) );
	convert_char_2_colmatr(data);
}

// AUXILIARY

pov Canvas::crd_change( const pov& pt ){
	return { pt.x, (H-1)-pt.y };

}

bool Canvas::pov_is_in( const pov& pt ){
	return ( 0 <= pt.x ) && (pt.x <= W-1 )
	    && ( 0 <= pt.y ) && (pt.y <= H-1 );
}

// SETTERS

void Canvas::set_pixel(pov pt_, const color COL){
	
	pov pt = crd_change( pt_ );
	
	if( pov_is_in( pt ) ){
		try{
			_canvas[pt.y][pt.x] = COL;
		}
		catch(...){
			std::cout << "Couldn't set pixel (" << pt.x << "," << pt.y << ")\n";
		}
	}
}

void Canvas::dye_all( const color COL ){
	
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			_canvas[i][j] = COL;
		}
	}
}

// AUXILIARY CONVERTATION

void Canvas::convert_char_2_colmatr(const unsigned char * data){
	try{
		switch( C ){

		case 1:
			conv_2colmatr_1( data );
			break;
		case 2:
			conv_2colmatr_2( data );
			break;
		case 3:
			conv_2colmatr_3( data );
			break;
		case 4:
			conv_2colmatr_4( data );
			break;
		}
	}
	catch(...){
		std::cout << "Couldn't convert char* to color-matrix!\n";
	}
}

void Canvas::conv_2colmatr_1( const unsigned char * data ){
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			int newcol = (int) data[ i*W + j ];
			_canvas[i][j] = { newcol, newcol, newcol, 255 };
		}
}

void Canvas::conv_2colmatr_2( const unsigned char * data ){
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			int newcol = (int) data[ 2*(i*W + j) ];
			_canvas[i][j] = { newcol, newcol, newcol,
						(int) data[ 2*(i*W + j) + 1 ] };
		}
}


void Canvas::conv_2colmatr_3( const unsigned char * data ){
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			_canvas[i][j] = { (int) data[ 3*(i*W + j)     ],
					  (int) data[ 3*(i*W + j) + 1 ],
					  (int) data[ 3*(i*W + j) + 2 ],
					  255 }; 
		}
}

void Canvas::conv_2colmatr_4( const unsigned char * data ){
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			_canvas[i][j] = { (int) data[ 4*(i*W + j)     ],
					  (int) data[ 4*(i*W + j) + 1 ],
					  (int) data[ 4*(i*W + j) + 2 ],
					  (int) data[ 4*(i*W + j) + 3 ] };
		}
}


void Canvas::convert_colmatr_2_char(char * data){
	try{
		switch( C ){
			
		case 1:
			conv_2char_1( data );
			break;
		case 2:
			conv_2char_2( data );
			break;
		case 3:
			conv_2char_3( data );
			break;
		case 4:
			conv_2char_4( data );
			break;
		}
	}
	catch(...){
		std::cout << "Couldn't convert color-matrix to char*!";
	}
}



void Canvas::conv_2char_1( char * data ){
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			data[ i*W + j ] = (char)(_canvas[i][j]).to_bw();
		}
}

void Canvas::conv_2char_2( char * data ){
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			data[ 2*(i*W + j)    ] = (char)(_canvas[i][j]).to_bw();
			data[ 2*(i*W + j) + 1] = (char)(_canvas[i][j]).alpha;
		}
}

void Canvas::conv_2char_3( char * data ){
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			data[ 3*(i*W + j) + 0 ] = (char)(_canvas[i][j]).r;
			data[ 3*(i*W + j) + 1 ] = (char)(_canvas[i][j]).g;
			data[ 3*(i*W + j) + 2 ] = (char)(_canvas[i][j]).b;
		}
}

void Canvas::conv_2char_4( char * data ){
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++){
			data[ 4*(i*W + j) + 0 ] = (char)(_canvas[i][j]).r;
			data[ 4*(i*W + j) + 1 ] = (char)(_canvas[i][j]).g;
			data[ 4*(i*W + j) + 2 ] = (char)(_canvas[i][j]).b;
			data[ 4*(i*W + j) + 3 ] = (char)(_canvas[i][j]).alpha;
		}
}



// OUTPUT

void Canvas::output(string filename){
	char data[H*W*C];
	convert_colmatr_2_char(data);
	stbi_write_png(filename.c_str(),W,H,C,data,W*C);
}



bool operator == (const Canvas& left, const Canvas& right){
	bool res = ( left.C == right.C ) &&
		   ( left.H == right.H ) &&
		   ( left.W == right.W );
	if(res)
		res = res && ( left._canvas == right._canvas );
	return res;
}

Canvas& Canvas::operator = (const Canvas& right){
	if( this == &right ){
		return *this;
	}
	H = right.H;
	W = right.W;
	C = right.C;
	_canvas = right._canvas;
	return *this;
}


const Canvas operator + (const Canvas& left, const Canvas& right){
	// Channels number: addition table
	// in this case addition is NOT commutative
	// (the second (horizontal) summand is meant to be the higher layer)
	//	+	1	2	3	4
	//	1	c	2	c	4
	//	2	c	2	c	4
	//	3	c	3	c	4
	//	4	c	4	c	4
	// mark c means that there is no need to calculate the sum:
	// the result will be just a copy of the second summand

	if ( (right.C)%2 == 1 ){
		Canvas sum = right;
		return sum;
	}

	int new_C = std::max( left.C, right.C );
	
	// TO DO
	// think of an addition algorithm

	
	// temporary crap:
	Canvas sum = right;
	return sum;
}
//
