#include "camera.h"
#include "scene.h"
#include "cstdio"

ray camera::cast(int x, int y)
{
	ray res;
	
	double xx, yy, zz;
	res.start = origin;
	xx = xmin + (xmax - xmin)*x / x_res;
	yy = ymin + (ymax - ymin)*y / y_res;
	zz = 0 - origin.z;
	res.setdirec(xx, yy, zz);
	res.intensity = color(1);
	if (y == 0)
	{
		printf("%d..\n", x);
	}
	return res;
}
