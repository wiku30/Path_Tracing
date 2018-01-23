#include "bezier.h"
#include <iostream>
#include <fstream>
using namespace std;

static bool init_flag = 0;
static const int maxn = 10;
static int C[maxn+1][maxn+1]; //directly find!
static int pow2[maxn + 1];

void init()
{
	for (int i = 0; i <= maxn; i++)
	{
		C[i][0] = 1;
		C[i][i] = 1;
		pow2[i] = 1 << i;
	}
	for (int n = 2; n <= maxn; n++)
	{
		for (int m = 1; m < n; m++)
		{
			C[n][m] = C[n - 1][m - 1] + C[n - 1][m];
		}
	}
	init_flag = 1;
}

int quad_solve(double A, double B, double C, double* x1, double* x2)
{
	*x1 = NAN;
	*x2 = NAN;
	if (A == 0)
	{
		if (B == 0)
			return 0;
		else
		{
			*x1 = -(C / B);
			return 1;
		}
	}
	else
	{
		B /= A;
		C /= A;
		A = 1;
		double delta = B*B - 4 * A*C;
		if (delta < 0)
			return 0;
		else if (delta == 0)
		{
			*x1 = -B / (2 * A);
			return 1;
		}
		else
		{
			double sqd = sqrt(delta);
			*x1 = (-B - sqd) / (2 * A);
			*x2 = (-B + sqd) / (2 * A);
			return 2;
		}
	}
}

inline bool inside(const vec3& in)
{
	if (in.y < -30 || in.y>30)
		return 0;
	if (in.z < 10 || in.z>70)
		return 0;
	return 1;
}

const vec3 bezier::findcross(const ray& in, double *pt, int *po)
{
	double dx = in.direc.x;
	double dy = in.direc.y;
	double dz = in.direc.z;
	double xs = in.start.x;
	double ys = in.start.y;
	double zs = in.start.z;
	double x0 = mat[0].x;
	double x1 = mat[1].x;
	double x2 = mat[2].x;
	double y0 = mat[0].y;
	double y1 = mat[1].y;
	double y2 = mat[2].y;

	//coef or quadratic
	double A = (dy * (x0 - 2 * x1 + x2) - dx * (y0 - 2 * y1 + y2));
	double B = 2 * (dy*(x1 - x2) - dx*(y1 - y2));
	double C = dy*(x2 - xs) - dx*(y2 - ys);

	//roots
	double t1, t2, nt, c1, c2;
	nt = quad_solve(A, B, C, &t1, &t2);

	*pt = NAN;
	*po = 0;
	if (nt == 0)
		return NOVEC;
	else
	{
		vec3 v = NOVEC;

		if (t1 < 0 || t1 > 1)
		{
			t1 = t2;
			t2 = NAN;
		}

		if (t1 < 0 || t1 > 1 || ISNAN(t1))
			return NOVEC;

		double X = (x0 - 2 * x1 + x2)*t1*t1 + 2 * (x1 - x2)*t1 + x2;
		double Y = (y0 - 2 * y1 + y2)*t1*t1 + 2 * (y1 - y2)*t1 + y2;
		if (abs(dx) > 1e-4)
		{
			c1 = (X - xs) / dx;
		}
		else
		{
			c1 = (Y - ys) / dy;
		}

		X = (x0 - 2 * x1 + x2)*t2*t2 + 2 * (x1 - x2)*t2 + x2;
		Y = (y0 - 2 * y1 + y2)*t2*t2 + 2 * (y1 - y2)*t2 + y2;
		if (abs(dx) > 1e-4)
		{
			c2 = (X - xs) / dx;
		}
		else
		{
			c2 = (Y - ys) / dy;
		}

		if (c1 > 1e-7)
		{
			v = in.start + c1 * in.direc;
			if (inside(v)) //v is the intersecting point
			{
				tmpt = t1;
				*pt = c1;
				tmpv = v;
				if (in.direc.dot(getnormal(v)) < 0)
					*po = 1;
				else
					*po = -1;
				return v;
				
			}
		}
		if (c2 > 1e-7)
		{
			v = in.start + c2 * in.direc;
			if (inside(v)) //v is the intersecting point
			{
				tmpt = t2;
				*pt = c2;
				tmpv = v;
				if (in.direc.dot(getnormal(v)) < 0)
					*po = 1;
				else
					*po = -1;
				return v;
				
			}
		}
		return NOVEC;
	}
}

const vec3 bezier::getnormal(const vec3& vec)
{
	assert(dot(vec-tmpv, vec-tmpv) < 1e-14);

	double x0 = mat[0].x;
	double x1 = mat[1].x;
	double x2 = mat[2].x;
	double y0 = mat[0].y;
	double y1 = mat[1].y;
	double y2 = mat[2].y;

	double dx = (x0 - 2 * x1 + x2)*tmpt - (x1 - x2);
	double dy = (y0 - 2 * y1 + y2)*tmpt - (y1 - y2);

	return vec3(-dy, dx, 0);
}

vec3 bezier::findPoint(double t, double u)
{
	if (!init_flag)
		init();
	vec3 res(0,0,0);
	int n = deg;
	res = t*t*mat[0] + 2 *t*(1 - t)*mat[1] + (1 - t)*(1 - t) * mat[2];
	res.z = 10 + 60 * u;
	return res;
}

void bezier::genMesh(int n)
{
	ofstream of("mesh/mesh.obj");
	vec3 mesh[30][30];
	double tick = 1.0 / (n-1);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mesh[i][j] = findPoint(tick*i, tick*j);
			vec3 p = mesh[i][j];
			of << "v " << p.x << " " << p.y << " " << p.z << endl;
		}
	}
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			of << "f " << i*n + j + 1 << " " << i*n + j + 2 << " " << (i + 1)*n + j + 1 << " " << (i + 1)*n + j + 2 << endl;
		}
	}
	of.close();

}

bezier::bezier()
{
	mat[0].set(25, -30, 10);
	mat[1].set(20.5, -7, 10);
	mat[2].set(25, 30, 10);
	tmpt = NAN;
	tmpv = NOVEC;
	mir_rate = 0.07;
	dif_rate = 0.00;
	mir_color = 1;
	dif_color = 1;
	refr_rate = 0.93;
	density = 1.33;
}

