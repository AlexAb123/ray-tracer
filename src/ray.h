#pragma once

#include "Vector3.h"

class Ray {

public:

	Vector3 origin;
	Vector3 dir;

	Ray(const Vector3& origin, const Vector3& dir) : origin(origin), dir(dir) {}

	Vector3 at(double t) const {
		return origin + (t * dir);
	}

};