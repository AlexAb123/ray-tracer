#pragma once
#include "ray.h"

class hitRecord {
public:
	Vector3 p;
	Vector3 normal;
	double t;
	bool front_face;

	//Sets the hit record normal vector.
	// NOTE: the parameter 'outwardNormal' is assumed to have unit length.
	void set_face_normal(const ray& r, const Vector3& outwardNormal) {
		front_face = dot(r.dir, outwardNormal) < 0;
		normal = front_face ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const ray& r, double rayTMin, double rayTMax, hitRecord& rec) const = 0;
};