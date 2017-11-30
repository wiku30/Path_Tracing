#pragma once

#include "types.h"

class triangle : public random_shape
{
protected:
	vec3 node[3];
	vec3 normal;
	double bias;	// dot(normal,node[i]) + bias == 0
public:
	triangle(const vec3& n0, const vec3& n1, const vec3& n2)
	{
		node[0] = n0;
		node[1] = n1;
		node[2] = n2;
		vec3 l1 = node[1] - node[0];
		vec3 l2 = node[2] - node[1];
		normal = l1.cross(l2);
		normal /= sqrt(normal.dot(normal));
		bias = - normal.dot(n0);
		mir_rate = 0.3;
		dif_rate = 0.5;
		mir_color = 1;
		dif_color = 1;
	}
	const bool ifcross(const ray& in);
	const vec3 findcross(const ray& in, double *pt = &dummyF, int *po = &dummyI);
	const vec3 getnormal(const ray& in);
	const TYPE type() { return TRIANGLE; }
};