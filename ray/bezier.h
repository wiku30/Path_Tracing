#pragma once
#include <cmath>
#include <vector>
#include "types.h"
using namespace std;

const double nann = 0.0 / 0.0;

const int deg = 2;

class bezier: public random_shape
{
	vec3 mat[deg+1][deg+1];
public:
	vec3 findPoint(double xx, double yy);
	void genMesh(int n=21);
	const virtual vec3 findcross(const ray&, double *pt = &dummyF, int *po = &dummyI) { return vec3(); }
	const virtual vec3 getnormal(const vec3&) { return vec3(); }
	const int type() { return 10; }

	bezier();
};
