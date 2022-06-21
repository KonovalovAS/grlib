#ifndef NOISE_ELIMINATOR_HPP_INCLUDED
#define NOISE_ELIMINATOR_HPP_INCLUDED

#include "canvas.hpp"
#include <vector>

using std::vector;

typedef vector<float> f_v;
typedef vector<f_v> f_matr;

enum eliminator{
	PERONA_MALIK,
	AVERAGER,
};

enum apply_to{
	ALL,
};

class Noise_eliminator{
private:
	float delta_t,
	      k,
	      Time;

	void get_f_matricies(Canvas& img, vector<f_matr>& data);
	void f_matricies_2_canvas(Canvas& img, const vector<f_matr>& data);
	float core( float x );
	void Perona_n_Malik(f_matr& data);

public:	
	Noise_eliminator( float k_ = 10, float delta_t_ = 0.2, float Time_ = 10 );
	void set_params( float k_ = 10, float delta_t_ = 0.2, float Time_ = 10 );
	
	void set_k( float k_ );
	void set_delta_t( float delta_t_ );
	void set_Time( float Time_ );

	void operator () (Canvas& img, eliminator ELIMINATOR, apply_to OPT = ALL);
};


#endif


