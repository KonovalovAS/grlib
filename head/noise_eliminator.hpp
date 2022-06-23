#ifndef NOISE_ELIMINATOR_HPP_INCLUDED
#define NOISE_ELIMINATOR_HPP_INCLUDED

#include "canvas.hpp"
#include "typedefs.hpp"

#include <vector>
using std::vector;

class Canvas;

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

	float core( float x );
	void Perona_n_Malik(float_matr& data);

public:	
	Noise_eliminator( float k_ = 10, float delta_t_ = 0.2, float Time_ = 10 );
	void set_params( float k_ = 10, float delta_t_ = 0.2, float Time_ = 10 );
	
	void set_k( float k_ );
	void set_delta_t( float delta_t_ );
	void set_Time( float Time_ );

	void operator () (Canvas& img, apply_to = ALL);
};


#endif


