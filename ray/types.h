#ifndef WIKU_TYPES
#define WIKU_TYPES

#include <opencv2/core/core.hpp>  
#include <math.h>
#include <iostream>


typedef cv::Point3d vec3;

class color: public vec3
{
public:
	
	color(double a)
	{
		x = a;
		y = a;
		z = a;
	}
	color()
	{
		x = 0;
		y = 0;
		z = 0;
	}
};

double dot(vec3, vec3);

class ray
{
public:
	vec3 start;
	vec3 direc;
	color intensity; //(r,g,b)
};

class shape
{
protected:
	color mir_rate;
	color dif_rate;

public:
	virtual bool ifcross(ray) = 0;
	virtual vec3 findcross(ray) = 0;
	virtual vec3 getnormal(ray) = 0;

	virtual ray reflect(ray);
};

class transparent : public shape
{
protected:
	double density;	//refraction rate
public:
	virtual ray refract(ray);
	transparent(){}
};

class random_shape : public transparent		//Monte Carlo
{
protected:

	color refr_rate;
public:
	random_shape(){}
};


#endif