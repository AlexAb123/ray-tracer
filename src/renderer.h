#pragma once
#include "Vector3.h"
#include "Ray.h"

double hitSphere(const Vector3& sphereCenter, const double sphereRadius, const Ray& r);
Vector3 rayColor(const Ray& r);