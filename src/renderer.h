#pragma once
#include "utils.h"
#include "hittable.h"

double hitSphere(const Vector3& sphereCenter, const double sphereRadius, const Ray& r);
Vector3 rayColor(const Ray& r, const Hittable& world);