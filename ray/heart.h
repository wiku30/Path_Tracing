#pragma once
#include "types.h"
#include <vector>
using namespace std;

class heart1 : public random_shape
{
	vec3 center;
	double size;
	double thickness;
	vector<vec3> bezier1;
	vector<vec3> bezier2;

};