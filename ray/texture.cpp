#include "texture.h"

const color tex_face::texture(const ray &in)
{
	color res(1);
	vec3 place = findcross(in);
	int xpix, zpix;
	xpix = int((place.x - xmin) / (xmax - xmin)*xres);
	zpix = int((place.z - zmin) / (zmax - zmin)*zres);
	if (xpix >= 0 && xpix < xres && zpix >= 0 && zpix < zres)
	{
		res.x *= data[xpix][zpix].x*data[xpix][zpix].x / 65536.0;
		res.y *= data[xpix][zpix].y*data[xpix][zpix].y / 65536.0;
		res.z *= data[xpix][zpix].z*data[xpix][zpix].z / 65536.0;
	}
	return res;
}

const color tex_face2::texture(const ray &in)
{
	color res(1);
	vec3 place = findcross(in);
	int xpix, ypix;
	xpix = int((place.x - xmin) / (xmax - xmin)*xres);
	ypix = int((place.y - ymin) / (ymax - ymin)*yres);
	if (xpix >= 0 && xpix < xres && ypix >= 0 && ypix < yres)
	{
		res.x *= data[xpix][ypix].x*data[xpix][ypix].x / 65536.0;
		res.y *= data[xpix][ypix].y*data[xpix][ypix].y / 65536.0;
		res.z *= data[xpix][ypix].z*data[xpix][ypix].z / 65536.0;
	}
	return res;
}