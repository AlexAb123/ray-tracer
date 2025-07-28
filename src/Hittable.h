#pragma once
#include "ray.h"

class HitRecord {

private:

	Vector3 m_point;
	Vector3 m_normal;
	double m_t;
	bool m_frontFace;

public:

	// Sets the hit record normal vector.
	// NOTE: the parameter 'outwardNormal' is assumed to have unit length.
	void setFaceNormal(const Ray& r, const Vector3& outwardNormal) {
		m_frontFace = dot(r.dir(), outwardNormal) < 0;
		m_normal = m_frontFace ? outwardNormal : -outwardNormal;
	}

	const Vector3& point() const { return m_point; }
	const Vector3& normal() const { return m_normal; }
	double t() const { return m_t; }
	bool frontFace() const { return m_frontFace; }

	void setPoint(const Vector3& point) { m_point = point; }
	void setT(double t) { m_t = t; }
};

class Hittable {
public:
	virtual ~Hittable() = default;
	// Updates parameter 'rec' with new hit information
	virtual bool hit(const Ray& r, double rayTMin, double rayTMax, HitRecord& rec) const = 0;
};