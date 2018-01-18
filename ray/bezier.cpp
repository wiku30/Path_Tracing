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

vec3 bezier::findPoint(double xx, double yy)
{
	if (!init_flag)
		init();
	vec3 res(0,0,0);
	int n = deg;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			res += mat[i][j] * C[n][i] *C[n][j] * pow(xx, i) * pow(1 - xx, n - i)
				* pow(yy, j) * pow(1 - yy, n - j);
		}
	}
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
	mat[0][0].set(22, -30, 70);
	mat[0][1].set(17, 0, 70);
	mat[0][2].set(22, 30, 70);
	mat[1][0].set(19, -30, 40);
	mat[1][1].set(27, 0, 40);
	mat[1][2].set(19, 30, 40);
	mat[2][0].set(22, -30, 10);
	mat[2][1].set(17, 0, 10);
	mat[2][2].set(22, 30, 10);
}

