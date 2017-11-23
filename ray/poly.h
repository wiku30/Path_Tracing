#include <cmath>
#pragma once
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> cmp;

class poly // at most 3 order
{
public:
	cmp a[4];
	poly(cmp x0, cmp x1, cmp x2, cmp x3);
	friend poly operator + (const poly&, const poly&);
	friend poly operator * (const poly&, const poly&);
	int solve(vector < cmp >&);
};