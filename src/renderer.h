#pragma once
#include "vector3.h"
#include "ray.h"

double hitSphere(const Vector3& sphereCenter, const double sphereRadius, const Ray& r);
Vector3 rayColor(const Ray& r);