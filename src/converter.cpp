#include "../head/converter.hpp"

#include <iostream>
#include <cmath>

// implementation

void Converter::uns_chars_to_color_matr( const unsigned char * data, color_matr& cmatr, int C ){
	
	int H = cmatr.size(),
	    W = cmatr[0].size();

	try{
		for(int i=0; i<H; i++){
			for(int j=0; j<W; j++){
				
				if( C %2 ){
					cmatr[i][j].alpha = 255;
				}
				else{
					cmatr[i][j].alpha =
						(int) data[ 2*(i*W + j) + C - 1 ];
				}
				
				if( C > 2 ){
					cmatr[i][j].r = (int) data[ C*(i*W+j)   ];
					cmatr[i][j].g = (int) data[ C*(i*W+j)+1 ];
					cmatr[i][j].b = (int) data[ C*(i*W+j)+2 ];
				}
				else{
					int newcol = (int) data[ i*W + j ];
					cmatr[i][j].r = newcol;
					cmatr[i][j].g = newcol;
					cmatr[i][j].b = newcol;
				}
			}
		}
	}
	catch(...){
		std::cout << "Couldn't convert char* to color-matrix!\n";
	}
}


void Converter::color_matr_to_chars( const color_matr& cmatr, char * data, int C ){
	
	int H = cmatr.size(),
	    W = cmatr[0].size();

	try{
		for(int i=0; i<H; i++){
			for(int j=0; j<W; j++){
				
				if( !( C%2 ) ){
					data[ C*(i*W +j) + C-1] = (char)(cmatr[i][j]).alpha;
				}
				
				if( C > 2 ){
					data[ C*(i*W + j) +0] = (char)(cmatr[i][j]).r;
					data[ C*(i*W + j) +1] = (char)(cmatr[i][j]).g;
					data[ C*(i*W + j) +2] = (char)(cmatr[i][j]).b;
				}
				else{
					data[ C*(i*W + j)] = (char)( (int)round( (float)
					  ( cmatr[i][j].r + cmatr[i][j].g + cmatr[i][j].b )/3 ) );
				}
			}
		}
	}
	catch( ... ){
		std::cout << "Couldn't convert color-matrix to char*!\n";
	}
}


//
