#include "types.h"

const double vec3::proj_t(const vec3& vect) const
{
	return dot(vect)/dot(*this);
}

double dot(vec3 a, vec3 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

color operator *(color a, color b)
{
	color c;
	c.x = a.x*b.x;
	c.y = a.y*b.y;
	c.z = a.z*b.z;
	return c;
}

const double ray::pedal_t(const vec3& point) const
{
	return direc.proj_t(point - start);
}

const ray shape::reflect(const ray& in)
{
	ray out(in);
	vec3 normal = getnormal(in);
	if (normal.isvalid())
	{
		out.start = findcross(in);
		out.direc = in.direc - 2 * normal.proj_vec(in.direc);
	}
	
	return out;
}

const ray transparent::refract(const ray& in) 
{
	// TODO: implement refract
	return ray();
}