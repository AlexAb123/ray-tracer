#pragma once
#include "vec3.h"
#include "ray.h"

double hitSphere(const vec3& sphereCenter, const double sphereRadius, const ray& r);
vec3 rayColor(const ray& r);