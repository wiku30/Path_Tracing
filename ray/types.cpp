#include "types.h"


double dot(vec3 a, vec3 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

ray shape::reflect(ray in)
{
	if (ifcross(in))
	{
		vec3 normal = getnormal(in);
		ray out(in);
		out.start = findcross(in);
		out.direc = in.direc -2 * dot(in.direc, normal) * normal / dot(normal, normal);
	}
}

ray transparent::refract(ray in) 
{
	// not finished yet
	return ray();
}