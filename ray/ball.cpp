#include "ball.h"

ball::ball(vec3 center_, double radius_)
{
	center = center_;
	radius = radius_;
	mir_rate = color(0.4);
	dif_rate = color(0.4);
	refr_rate = color(0);
}

bool ball::ifcross(ray in)
{

}