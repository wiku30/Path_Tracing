#pragma once
#include <cmath>
#include <vector>
#include "types.h"
using namespace std;

const double nann = 0.0 / 0.0;

vec3 findPoint(const vector<vec3> points, double place);

double findCross2D(const vector<vec3>& points, const ray& cast); //xz plane