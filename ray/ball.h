#pragma once
#include "types.h"

class ball : public random_shape
{
protected:
	vec3 center;
	double radius;
public:
	ball(){}
	ball(vec3 center_, double radius_, color emission_ = 0, double mir = 0.9, double dif = 0,
		color mirc = 1, color difc = 1, double rfr = 0);
	const vec3 findcross(const ray& in, double *pt = &dummyF, int *po = &dummyI);
	const vec3 getnormal(const vec3& in);
	const TYPE type() { return BALL; }
};