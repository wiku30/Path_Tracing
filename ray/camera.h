#pragma once
#include "types.h"



class camera	


//For simplicity, the perspective is from (0, 0, -10)
//The film is at (+-7, +-7, 0)

// 501 * 501
{
	vec3 origin;

public:
	double xmin, xmax, ymin, ymax;
	static const int x_res = RES, y_res = RES;
	camera() : xmin(-7), xmax(7), ymin(-7), ymax(7), origin(0, 0, -10) {}
	color pic[x_res + 1][y_res + 1];
	ray cast(int x, int y);
};