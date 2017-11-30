#include "types.h"
#include <cmath>

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
		out.intensity = out.intensity * mir_color;
	}
	
	return out;
}

const ray shape::diffuse(const ray& in)
{
	ray out(in);
	vec3 normal = getnormal(in);
	if (normal.isvalid())
	{
		normal /= normal.abs();
		if (normal.dot(in.direc) > 0)
			normal = -normal;
		double ra, rb, p;
		ra = (rand() % 4096) / 4096.0;
		rb = (rand() % 4096) / 4096.0 * 2 * 3.14159265357932;
		p = sqrt(1 - ra*ra);
		vec3 m1(1, 0, 0), m2(0, 1, 0);
		vec3 vert1 = normal.cross(m1);
		if (vert1.abs() < 0.1)
			vert1 = normal.cross(m2);
		vert1 /= vert1.abs();
		vec3 vert2 = normal.cross(vert1);

		out.direc = normal*ra + p*vert1*cos(rb) + p*vert2*sin(rb);

		out.intensity = out.intensity * dif_color;
	}

	return out;
}

const ray transparent::refract(const ray& in) 
{
	// TODO: implement refract
	return ray();
}