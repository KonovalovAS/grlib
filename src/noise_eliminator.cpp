#include "../head/noise_eliminator.hpp"
#include "../head/converter.hpp"
#include "../head/canvas.hpp"

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

void Noise_eliminator::operator () (Canvas& img, apply_to OPT){
	
	
	vector<float_matr> data;
	Converter::color_matr_to_float_matr_layers( img._canvas, data, img.C, 1 );
	std::cout << "Converted successfully!" << std::endl;

	switch( OPT ){
	case ALL:
		for( int col=0; col<img.C; col++ ){
			Perona_n_Malik(data[col]);
		}
		break;
	}

	Converter::float_matr_layers_to_color_matr( data, img._canvas );
	std::cout << "Converted back successfully!" << std::endl;
}

float Noise_eliminator::core( float x ){
	return 1.0/( 1.0 + pow( x/k, 2 ) );
}

// I know the way to speed this up by at least 2 times,
// not done yet
void Noise_eliminator::Perona_n_Malik(float_matr& data){
	
	float n,s,e,w; // north, south, east, west
	float timer = Time;

	int H = data.size()-2;
	int W = data[0].size()-2;

	// main process:
	while( timer > 0 ){
		auto buf = data;
		
		std::cout << 1 - timer/Time << std::endl;
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
