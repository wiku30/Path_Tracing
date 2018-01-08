#pragma once

#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <cmath>
#include <stdio.h>

using namespace cv;

#include "triangle.h"

class tex_face : public triangle
{
	color data[80][100];
	double xmin, xmax, zmin, zmax;
	int xres, zres;
public:
	tex_face() : triangle(vec3(-30, -29.999, -1000), vec3(-30, -29.999, 1000), vec3(2000, -29.999, 0))
	{
		xmin = -17;
		xmax = 17;
		zmin = 27.5;
		zmax = 70;
		xres = 80;
		zres = 100;
		mir_rate = 0;
		dif_rate = 0.9;
		Mat pic = imread("texture/iiis.jpg");
		for (int i = 0; i < xres; i++)
		{
			for (int j = 0; j < zres; j++)
			{
				data[i][j].x = pic.at<Vec3b>(i, j)[0];
				data[i][j].y = pic.at<Vec3b>(i, j)[1];
				data[i][j].z = pic.at<Vec3b>(i, j)[2];
			}
		}
	}

	virtual const color texture(const ray& in);


};

class tex_face2 : public triangle
{
	color data[850][850];
	double xmin, xmax, ymin, ymax;
	int xres, yres;
public:
	tex_face2() : triangle(vec3(-30, -1000, 69.999), vec3(-30, 1000, 69.999), vec3(2000, 0, 69.999))
	{
		xmin = -30;
		xmax = 30;
		ymin = -30;
		ymax = 30;
		xres = 850;
		yres = 850;
		mir_rate = 0;
		dif_rate = 0.9;
		Mat pic = imread("texture/wiku.jpg");
		for (int i = 0; i < xres; i++)
		{
			for (int j = 0; j < yres; j++)
			{
				data[i][j].x = pic.at<Vec3b>(i, j)[0];
				data[i][j].y = pic.at<Vec3b>(i, j)[1];
				data[i][j].z = pic.at<Vec3b>(i, j)[2];
			}
		}
	}

	virtual const color texture(const ray& in);


};