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

void Converter::color_matr_to_float_matr_layers( const color_matr& cmatr, vector<float_matr>& data, int C, int border ){
	
	int H = cmatr.size(),
	    W = cmatr[0].size();

	data = vector<float_matr>( C, float_matr( H+2*border, float_vec( W+2*border,0 ) ) );

	for(int y=0; y<H; y++){
		for(int x=0; x<W; x++){
			color tmp = cmatr[y][x];
			
			if( C<3 ){
				data[0][y+border][x+border] = (float) ( round( (float)(tmp.r + tmp.g + tmp.b)/3 ) );	
			}
			else{
				data[0][y+border][x+border] = (float) tmp.r;
				data[1][y+border][x+border] = (float) tmp.g;
				data[2][y+border][x+border] = (float) tmp.b;
			}

			if( !(C%2) ){
				data[C-1][y+border][x+border] = (float) tmp.alpha;
			}

		}
	}


}

void Converter::float_matr_layers_to_color_matr( const vector<float_matr>& data, color_matr& cmatr ){
	int C = data.size(),
	    H_b = data[0].size(),
	    W_b = data[0][0].size(),
	    H = cmatr.size(),
	    W = cmatr[0].size(),
	    border = H_b - H;
	
	for(int y=0; y<H; y++){
		for(int x=0; x<W; x++){
			
			cmatr[y][x].alpha = !(C%2) ? 255 : ( (int) round( data[C-1][y+border][x+border] ) ); 
			
			cmatr[y][x].r = (int) round( data[0][y+border][x+border] );

			cmatr[y][x].g = (C<2) ? ( (int) round( data[0][y+border][x+border] ) )
					      : ( (int) round( data[1][y+border][x+border] ) );
			
			cmatr[y][x].b = (C<2) ? ( (int) round( data[0][y+border][x+border] ) )
					      : ( (int) round( data[2][y+border][x+border] ) );
		}
	}

}



//
