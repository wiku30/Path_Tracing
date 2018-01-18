#ifndef WIKU_TYPES
#define WIKU_TYPES

#define HI_RES 1

#if HI_RES
#define RES 600
#define PRECISION 1500

#else

#define RES 240
#define PRECISION 469

#endif

#define ITER_DEPTH 40


#include <opencv2/core/core.hpp>  
#include <math.h>
#include <iostream>

#define TYPE int
#define BALL 1
#define TRIANGLE 2


static double dummyF;
static int dummyI;

inline bool ISNAN(double x)
{
	return x != x;
}

class vec3 : public cv::Point3d
{
public:
	vec3() {}
	vec3(const cv::Point3d &p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	vec3(double x_, double y_, double z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	void set(double x_, double y_, double z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	const double abs() const
	{
		return sqrt(dot(*this));
	}
	const double proj_t(const vec3&) const;	//find a multiple to be the projection of another vector
	const vec3 proj_vec(const vec3& vec) const
	{ 
		return proj_t(vec) * (*this); 
	}
	const bool isvalid() const
	{ 
		return !ISNAN(x); 
	}
};

const vec3 NOVEC(NAN, NAN, NAN);


class color: public vec3
{
public:
	
	color(double a)
	{
		x = a;
		y = a;
		z = a;
	}

	color(double a, double b, double c)
	{
		x = a;
		y = b;
		z = c;
	}
	
	color()
	{
		x = 0;
		y = 0;
		z = 0;
	}
};

color operator *(color, color);

double dot(vec3, vec3);


class ray
{
public:
	vec3 start;
	vec3 direc;
	color intensity; //(r,g,b)
	const double pedal_t(const vec3&) const;
	void setstart(double x, double y, double z)
	{
		start = vec3(x, y, z);
	}
	void setdirec(double x, double y, double z)
	{
		direc = vec3(x, y, z);
	}
	const vec3 t2xyz(double t) const
	{
		return start + t * direc;
	}
	const vec3 pedal_xyz(const vec3& point) const
	{
		return t2xyz(pedal_t(point));
	}
};

class shape
{
protected:


public:
	color emit;
	double mir_rate;
	double dif_rate;
	color mir_color;
	color dif_color;
	const virtual vec3 findcross(const ray&, double *pt = &dummyF, int *po = &dummyI) = 0;
	// pt: the t value, po: 1 from outside, -1 from inside
	const virtual vec3 getnormal(const vec3&) = 0;
	const virtual TYPE type() = 0;

	const virtual ray reflect(const ray&);
	const virtual ray diffuse(const ray&);
	const virtual color texture(const ray&) { return 1; }
	const virtual color emission(const ray&)
	{
		return color(emit);
	}
};

class transparent : public shape
{
protected:
	double density = 1.5;	//refraction rate
public:
	const virtual ray refract(const ray&);
	transparent(){}
};

class random_shape : public transparent		//Monte Carlo
{
public:
	double refr_rate;
	random_shape(){}
};


#endif