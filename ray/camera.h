#pragma once
#include "types.h"

class camera	
//For simplicity, the perspective is from (0, 0, -10)
//The film is at (+-5, +-5, 0)

// 501 * 501
{
	vec3 origin;

public:
	double xmin, xmax, ymin, ymax;
	static const int x_res = 50, y_res = 50;
	camera() : xmin(-5), xmax(5), ymin(-5), ymax(5), origin(0, 0, -10) {}
	color pic[x_res + 1][y_res + 1];
	ray cast(int x, int y);
};