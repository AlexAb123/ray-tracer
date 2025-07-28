#pragma once

#include "vec3.h"

class ray {

public:

	vec3 origin;
	vec3 dir;

	ray(const vec3& origin, const vec3& dir) : origin(origin), dir(dir) {}

	vec3 at(double t) const {
		return origin + t * dir;
	}

};