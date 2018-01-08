#include "camera.h"
#include "scene.h"
#include "cstdio"

ray camera::cast(int x, int y)
{
	ray res;

	double xx, yy, zz;
	if (y == 0 && !(x % 5))
	{
		printf("%d..\n", x);
	}
	res.start = origin;
	xx = xmin + (xmax - xmin)* (x + (rand() % 4096) / 4096.0) / x_res;
	yy = ymin + (ymax - ymin)* (y + (rand() % 4096) / 4096.0) / y_res;
	//upsampling

	zz = 0 - origin.z;
	res.setdirec(xx, yy, zz);
	res.intensity = color(1);

	return res;
}
