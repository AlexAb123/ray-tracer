#pragma once

#include "vector3.h"

class Ray {

private:
	Vector3 m_origin;
	Vector3 m_direction;

public:

	Ray() {}
	Ray(const Vector3& origin, const Vector3& direction) : m_origin(origin), m_direction(direction) {}

	const Vector3& origin() const { return m_origin; }
	const Vector3& direction() const { return m_direction; }

	Vector3 at(double t) const {
		return m_origin + (t * m_direction);
	}
};