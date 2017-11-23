#ifndef WIKU_TYPES
#define WIKU_TYPES

#include <opencv2/core/core.hpp>  
#include <math.h>
#include <iostream>


typedef cv::Point3d vec3;

class arrow3
{
public:
	vec3 vec;
	arrow3(double x, double y, double z)
	{
		double norm = sqrt(x*x + y*y + z*z);
		vec.x = x / norm;
		vec.y = y / norm;
		vec.z = z / norm;
	}
	arrow3(vec3 v)
	{
		double norm = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		vec = v / norm;
	}
};

class ray
{
public:
	vec3 start;
	arrow3 direc;
	double intensity;

};

class shape
{
public:
	virtual bool ifcross(ray) = 0;
	virtual vec3 findcross(ray) = 0;
	virtual ray reflect(ray) = 0;
};

class transparent : public shape
{
	double density;	//refraction rate
public:
	virtual ray refract(ray) = 0;
};

class random_shape : public transparent		//Monte Carlo
{
	double dif_rate;
	double mir_rate;
	double refr_rate;
};


#endif