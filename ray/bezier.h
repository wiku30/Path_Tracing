#pragma once
#include <cmath>
#include <vector>
#include "types.h"
using namespace std;


const int deg = 2;

class bezier: public random_shape
{
	vec3 mat[deg+1];
	double tmpt;
	vec3 tmpv;
public:
	vec3 findPoint(double xx, double yy);
	void genMesh(int n=21);
	const virtual vec3 findcross(const ray&, double *pt = &dummyF, int *po = &dummyI);
	const virtual vec3 getnormal(const vec3&);
	const int type() { return 10; }
	bezier();
};
