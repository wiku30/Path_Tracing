#pragma once

#include <vector>
#include "types.h"
#include "camera.h"

using std::vector;

class scene
{
	vector<random_shape*> shapes;
	camera& view;
	static const int repeat = PRECISION;
	static const int depth = ITER_DEPTH;
public:
	scene(camera& v): view(v){}
	void add_shape(random_shape*);
	//void set_view(const camera&);
	color draw(const ray&);
	color trace(const ray&, int TTL);
	void shoot();
};