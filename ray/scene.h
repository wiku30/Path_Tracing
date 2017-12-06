#pragma once

#include <vector>
#include "types.h"
#include "camera.h"

using std::vector;

class scene
{
	vector<shape*> shapes;
	camera& view;
	static const int repeat = 200;
	static const int depth = 10;
public:
	scene(camera& v): view(v){}
	void add_shape(shape*);
	//void set_view(const camera&);
	color draw(const ray&);
	color trace(const ray&, int TTL);
	void shoot();
};