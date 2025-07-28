#pragma once

#include "vector3.h"

class Ray {

private:
	Vector3 m_origin;
	Vector3 m_dir;

public:

	Ray(const Vector3& origin, const Vector3& dir) : m_origin(origin), m_dir(dir) {}

	const Vector3& origin() const { return m_origin; }
	const Vector3& dir() const { return m_dir; }

	Vector3 at(double t) const {
		return m_origin + (t * m_dir);
	}
};