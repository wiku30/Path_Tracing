#include "scene.h"
#include <iterator>
#include <cmath>

using namespace std;

void scene::add_shape(random_shape* s)
{
	shapes.push_back(s);
}

color scene::draw(const ray& r)
{
	color res;
	for (int i = 0; i < repeat; i++)
	{
		res += trace(r, depth) / repeat;
	}
	return res;
}

color scene::trace(const ray& r, int TTL)
{
	if (TTL <= 0 || r.intensity.dot(r.intensity) < 0.005*0.005)
		return color(0);

	double mint = 1e+308;
	random_shape* first_shape;
	vec3 see_point;
	vec3 temp;
	double t;
	size_t n = shapes.size();
	int flag = 0;
	for (size_t i=0; i < n; i++)
	{
		temp = shapes[i]->findcross(r, &t);
		if (t < mint) //update
		{
			flag = 1;
			first_shape = shapes[i];
			see_point = temp;
			mint = t;
		}
	}
	if (!flag)
		return 0;
	int rnd = rand() % 4096;
	int mir_thres = 4096 * (first_shape->mir_rate);
	int dif_thres = 4096 * (first_shape->mir_rate + first_shape->dif_rate);
	int refr_thres = 4096 * (first_shape->mir_rate + first_shape->dif_rate + first_shape->refr_rate);
	color c(0);
	c += first_shape->emission(r) * r.intensity;
	if (rnd < mir_thres) //mirror
	{
		c += trace(first_shape->reflect(r), TTL - 1) * first_shape->texture(r);
	}
	else if (rnd < dif_thres) //diffusion
	{
		c += trace(first_shape->diffuse(r), TTL - 1) * first_shape->texture(r); 
	}
	else if (rnd < refr_thres)
	{
		c += trace(first_shape->refract(r), TTL - 1) * first_shape->texture(r);
	}
	return c;
}

void scene::shoot()
{
	for (int i = 0; i < view.y_res; i++)
	{
		for (int j = 0; j < view.y_res; j++)
		{
			view.pic[i][j] = draw(view.cast(i, j));
		}
	}
}