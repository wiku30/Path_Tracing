#include "poly.h"

poly::poly(cmp x0, cmp x1, cmp x2, cmp x3)
{
	a[0] = x0;
	a[1] = x1;
	a[2] = x2;
	a[3] = x3;
}

poly operator +(const poly& a, const poly& b)
{
	poly res(a);
	for (int i = 0; i < 4; i++)
	{
		res.a[i] += b.a[i];
	}
	return res;
}

poly operator *(const poly& a, const poly& b)
{
	poly res(0,0,0,0);
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < k; i++)
		{
			res.a[k] += a.a[i] * b.a[k - i];
		}
	}
	return res;
}
