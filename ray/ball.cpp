#include "ball.h"

#define EPS 1e-7

ball::ball(vec3 center_, double radius_)
{
	center = center_;
	radius = radius_;
	mir_rate = color(0.4);
	dif_rate = color(0.4);
	refr_rate = color(0);
}

const bool ball::ifcross(const ray& in)
{
	return findcross(in).isvalid();
}

const vec3 ball::findcross(const ray& in, double *pt, int *po)
{
	double pedal_t = in.pedal_t(center);
	vec3 pedal = in.t2xyz(pedal_t);
	double d2 = dot(center - pedal, center - pedal);
	double mag2 = dot(in.direc, in.direc);
	double delta = (radius * radius - d2) / mag2;
	double mag = sqrt(mag2);
	*po = 0;
	if (delta < 0)			//not passing
		return NOVEC;
	double dt = sqrt(delta);
	double t1 = pedal_t - dt;
	double t2 = pedal_t + dt;
	if (t2*mag < EPS)		//outside, leaving
	{
		*pt = NAN;
		return NOVEC;
	}
	if (t1*mag < EPS)		//inside
	{
		*pt = t2;
		*po = -1;
		return in.t2xyz(t2);
	}
	else					//outside, approaching
	{
		*pt = t1;
		*po = 1;
		return in.t2xyz(t1);
	}

}

const vec3 ball::getnormal(const ray& in)
{
	vec3 v = findcross(in);
	if (v.isvalid())
		return v - center;
	return NOVEC;
}