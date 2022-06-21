#include "../head/noise_eliminator.hpp"

#include <cmath>

#include <iostream>

Noise_eliminator::Noise_eliminator( float k_, float delta_t_, float Time_ ){
	k = k_;
	delta_t = delta_t_;
	Time = Time_;
}

void Noise_eliminator::set_params( float k_, float delta_t_, float Time_ ){
	k = k_;
	delta_t = delta_t_;
	Time = Time_;
}

void Noise_eliminator::set_k( float k_ ){
	k = k_;
}
void Noise_eliminator::set_delta_t( float delta_t_ ){
	delta_t = delta_t_;
}
void Noise_eliminator::set_Time( float Time_ ){
	Time = Time_;
}

void Noise_eliminator::get_f_matricies( Canvas& img, vector<f_matr>& data){
	
	// plus one-pixel wide empty (black) border
	data = vector<f_matr>( img.C, f_matr( img.H+2, f_v( img.W+2,100 ) ) );

	for(int y=0; y<img.H; y++)
		for(int x=0; x<img.W; x++){
			color tmp = img.get_pixel( {x,y} );
			switch( img.C ){
			case 1:
				data[0][y+1][x+1] = (float) tmp.to_bw();
				break;
			case 2:
				data[0][y+1][x+1] = (float) tmp.to_bw();
				data[1][y+1][x+1] = (float) tmp.alpha;
				break;
			case 3:
				data[0][y+1][x+1] = (float) tmp.r;
				data[1][y+1][x+1] = (float) tmp.g;
				data[2][y+1][x+1] = (float) tmp.b;
				break;
			case 4:
				data[0][y+1][x+1] = (float) tmp.r;
				data[1][y+1][x+1] = (float) tmp.g;
				data[2][y+1][x+1] = (float) tmp.b;
				data[3][y+1][x+1] = (float) tmp.alpha;
				break;
			}
		}
}

void Noise_eliminator::f_matricies_2_canvas(Canvas& img, const vector<f_matr>& data){
	
	int C = data.size(),
	    H = data[0].size()-2,
	    W = data[0][0].size()-2;
	
	for(int y=0; y<H; y++)
		for(int x=0; x<W; x++){
			int r,g,b,alpha;
			
			switch( C ){
			case 1:
				r = std::max( (int)round(data[0][y+1][x+1]), 0 );
				g = r; b = r;
				alpha = 255;
				break;
			case 2:
				r = std::max( (int)round(data[0][y+1][x+1]), 0 );
				g = r; b = r;
				alpha = std::max( (int)round(data[1][y+1][x+1]), 0 );
				break;
			case 3:
				r = std::max( (int)round(data[0][y+1][x+1]), 0 );
				g = std::max( (int)round(data[1][y+1][x+1]), 0 );
				b = std::max( (int)round(data[2][y+1][x+1]), 0 );
				alpha = 255;
				break;
			case 4:
				r = std::max( (int)round(data[0][y+1][x+1]), 0 );
				g = std::max( (int)round(data[1][y+1][x+1]), 0 );
				b = std::max( (int)round(data[2][y+1][x+1]), 0 );
				alpha = std::max( (int)round(data[3][y+1][x+1]), 0 );
				break;
			}

			color newcol = { std::min( 255, r),
					 std::min( 255, g),
					 std::min( 255, b),
					 std::min( 255, alpha) };
			img.set_pixel( {x,y}, newcol );
		}
}

void Noise_eliminator::operator () (Canvas& img, apply_to OPT){
	
	
	vector<f_matr> data;
	get_f_matricies(img,data);

	switch( OPT ){
	case ALL:
		for( int col=0; col<img.C; col++ ){
			Perona_n_Malik(data[col]);
		}
		break;
	}

	f_matricies_2_canvas(img,data);
}

float Noise_eliminator::core( float x ){
	return 1.0/( 1.0 + pow( x/k, 2 ) );
}

void Noise_eliminator::Perona_n_Malik(f_matr& data){
	
	float n,s,e,w; // north, south, east, west
	float timer = Time;

	int H = data.size()-2;
	int W = data[0].size()-2;

	// main process:
	while( timer > 0 ){
		auto buf = data;
		
		for(int y=1; y<H+1; y++)
			for(int x=1; x<W+1; x++){
				n = buf[y-1][x] - buf[y][x];
				s = buf[y+1][x] - buf[y][x];
				e = buf[y][x+1] - buf[y][x];
				w = buf[y][x-1] - buf[y][x];
				float add = delta_t * (
						n*core(n)
					      + s*core(s)
					      + e*core(e)
					      + w*core(w) );
				data[y][x] += add;
			}
		timer -= delta_t;
	}
	
}
//
