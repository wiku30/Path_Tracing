#include "ball.h"

#define EPS 1e-7

ball::ball(vec3 center_, double radius_, color emit_)
{
	center = center_;
	radius = radius_;
	emit = emit_;
	mir_rate = 0.4;
	dif_rate = 0.6;
	mir_color = color(1);
	dif_color = color(1);
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
	*pt = NAN;
	if (delta < 0)			//not passing
	{
		*pt = NAN;
		return NOVEC;
	}
		
	double dt = sqrt(delta);
	double t1 = pedal_t - dt;
	double t2 = pedal_t + dt;
	if (t2*mag < EPS)		//outside, leaving
	{
		*pt = NAN;
		return NOVEC;
	}
	if (t1*mag < -EPS)		//inside
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