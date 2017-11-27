#pragma once
#include "types.h"

class ball : public random_shape
{
	vec3 center;
	double radius;
public:
	ball(vec3 center_, double radius_);
	bool ifcross(ray in);
	vec3 findcross(ray in);
	vec3 normal(ray in);
};