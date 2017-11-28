#pragma once
#include "types.h"

class ball : public random_shape
{
protected:
	vec3 center;
	double radius;
public:
	ball(){}
	ball(vec3 center_, double radius_);
	const bool ifcross(const ray& in);
	const vec3 findcross(const ray& in, double *pt = &dummyF, int *po = &dummyI);
	const vec3 getnormal(const ray& in);
	const TYPE type() { return BALL; }
};