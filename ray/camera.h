#pragma once
#include "types.h"



class camera	


//For simplicity, the perspective is from (0, 0, -14.99)
//The film is at (+-8, +-8, 0)

// 501 * 501
{
	vec3 origin;

public:
	double xmin, xmax, ymin, ymax;
	static const int x_res = RES, y_res = RES;
	camera() : xmin(-7.3), xmax(7.3), ymin(-7.3), ymax(7.3), origin(0, 0, -12) {}
	color pic[x_res + 1][y_res + 1];
	ray cast(int x, int y);
};