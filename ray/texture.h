#pragma once

#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <cmath>
#include <stdio.h>

using namespace cv;

#include "triangle.h"

class tex_face : public triangle
{
	color data[500][500];
	double xmin, xmax, ymin, ymax;
	int res;
public:
	tex_face(): triangle(vec3(-100, -100, 70), vec3(-100, 100, 70), vec3(200, 0, 70))
	{
		xmin = -30;
		xmax = 30;
		ymin = -30;
		ymax = 30;
		res = 500;
		mir_rate = 0;
		dif_rate = 0;
		Mat pic = imread("texture/wiku.jpg");
		/*namedWindow("游戏原画");   
		imshow("游戏原画", pic);*/
		for (int i = 0; i < 500; i++)
		{
			if (!(i % 25))
			{
				printf("%d\n", i);
			}
			for (int j = 0; j < 500; j++)
			{
				data[i][j].x = pic.at<Vec3b>(i, j)[0];
				data[i][j].y = pic.at<Vec3b>(i, j)[1];
				data[i][j].z = pic.at<Vec3b>(i, j)[2];
			}
		}
	}

	const color emission(const ray& r)
	{
		vec3 place = findcross(r);
		int xpix, ypix;
		xpix = int((place.x - xmin) / (xmax - xmin)*res);
		ypix = int((place.y - ymin) / (ymax - ymin)*res);
		if (xpix >= 0 && xpix < res && ypix >= 0 && ypix < res)
		{
			color res;
			res.x = data[xpix][ypix].x*data[xpix][ypix].x / 65536.0;
			res.y = data[xpix][ypix].y*data[xpix][ypix].y / 65536.0;
			res.z = data[xpix][ypix].z*data[xpix][ypix].z / 65536.0;
			return res;
		}
		else
		{
			return 0;
		}
	}

};