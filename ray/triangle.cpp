#include "triangle.h"
#include "iostream"
using namespace std;

const vec3 triangle::getnormal(const vec3& in)
{
	return normal;
}

const vec3 triangle::findcross(const ray& in, double *pt, int *po)
{
	double vn = in.direc.dot(normal);
	double pot = normal.dot(in.start) + bias;
	if (abs(vn) < 1e-7)
	{
		*pt = NAN;
		*po = 0;
		return NOVEC;
	}
	double t = -pot / vn;
	vec3 p = in.t2xyz(t);	//intersection with the plane
	if (t < 1e-7)	
	{
		*pt = NAN;
		*po = 0;
		return NOVEC;
	}
	//judge if p is within the triangle
	double S1, S2, S3, S;
	vec3 l1, l2, l3, c1, c2, c3, c;
	l1 = node[0] - p;
	l2 = node[1] - p;
	l3 = node[2] - p;
	c1 = l1.cross(l2);
	c2 = l2.cross(l3);
	c3 = l3.cross(l1);
	c = c1 + c2 + c3;
	S1 = c1.abs();
	S2 = c2.abs();
	S3 = c3.abs();
	S = c.abs();
	if (S1 + S2 > S || S2 + S3 > S || S3 + S1 > S)	//not within
	{
		*pt = NAN;
		*po = 0;
		return NOVEC;
	}
	else
	{
		*pt = t;
		*po = vn > 0 ? -1 : 1;
		return p;
	}
}
