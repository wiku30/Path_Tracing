#include "bezier.h"

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

vec3 findPoint(const vector<vec3> points, double place)
{
	if (!init_flag)
		init();
	vec3 res(0,0,0);
	int n = points.size() - 1;
	for (int i = 0; i <= n; i++)
	{
		res.x += points[i].x * C[n][i] * pow(place, i) * pow(1 - place, n-i);
		res.y += points[i].y * C[n][i] * pow(place, i) * pow(1 - place, n-i);
		res.z += points[i].z * C[n][i] * pow(place, i) * pow(1 - place, n-i);
	}
	return res;
}

double findCross2D(const vector<vec3>& points, const ray& cast)
{
	
}