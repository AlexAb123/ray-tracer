#pragma once
#include "utils.h"

class Material;

class HitRecord {

private:

	Vector3 m_point;
	Vector3 m_normal;
	shared_ptr<Material> m_material;
	double m_t;
	bool m_frontFace; // Whether or not it is the outward surface of the object

public:
	HitRecord() : m_point(), m_normal(), m_t(0.0), m_frontFace(false) {}

	// Sets the hit record normal vector.
	// NOTE: the parameter 'outwardNormal' is assumed to have unit length.
	void setFaceNormal(const Ray& r, const Vector3& outwardNormal) {
		m_frontFace = dot(r.direction(), outwardNormal) < 0;
		m_normal = m_frontFace ? outwardNormal : -outwardNormal;
	}

	const Vector3& point() const { return m_point; }
	const Vector3& normal() const { return m_normal; }
	const shared_ptr<Material>& material() const { return m_material; }
	double t() const { return m_t; }
	bool frontFace() const { return m_frontFace; }

	void setPoint(const Vector3& point) { m_point = point; }
	void setT(double t) { m_t = t; }
	void setMaterial(shared_ptr<Material> material) { m_material = material; }
};

class Hittable {
public:
	virtual ~Hittable() = default;
	// Updates parameter 'rec' with new hit information
	virtual bool hit(const Ray& r, Interval rayT, HitRecord& rec) const = 0;
};