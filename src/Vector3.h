#pragma once

#include "utils.h"

class Vector3 {

private:
	double m_x, m_y, m_z;

public:

	Vector3() : m_x(0), m_y(0), m_z(0) {}
	Vector3(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}
	Vector3(double value) : m_x(value), m_y(value), m_z(value) {}

	double x() const { return m_x; }
	double y() const { return m_y; }
	double z() const { return m_z; }

	Vector3 operator+(const Vector3& other) const {
		return Vector3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
	}

	Vector3& operator+=(const Vector3& other) {
		m_x += other.m_x;
		m_y += other.m_y;
		m_z += other.m_z;
		return *this;
	}

	Vector3 operator-(const Vector3& other) const {
		return Vector3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
	}

	Vector3 operator-() const {
		return Vector3(-m_x, -m_y, -m_z);
	}

	Vector3& operator-=(const Vector3& other) {
		m_x -= other.m_x;
		m_y -= other.m_y;
		m_z -= other.m_z;
		return *this;
	}

	Vector3 operator*(double scalar) const {
		return Vector3(m_x * scalar, m_y * scalar, m_z * scalar);
	}

	Vector3& operator*=(double scalar) {
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		return *this;
	}

	Vector3 operator/(double scalar) const {
		return Vector3(m_x / scalar, m_y / scalar, m_z / scalar);
	}

	Vector3& operator/=(double scalar) {
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		return *this;
	}

	double length() const {
		return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	double lengthSquared() const {
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}

	// Normalizes vectors with non-zero length.
	Vector3 normalize() const {
		return *this / length();
	}

	static Vector3 random() {
		return Vector3(randomDouble(), randomDouble(), randomDouble());
	}

	static Vector3 random(double min, double max) {
		return Vector3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}

	// Returns an evenly distributed random unit vector sphere on the unit sphere.
	static Vector3 randomUnitVector() {
		while (true) {
			Vector3 p = Vector3::random(-1, 1);
			double lensq = p.lengthSquared();
			// Only keep vectors that are in or on the unit sphere before normalization to keep a uniform distribution
			// Avoid vectors with really small lengths because of floating point precision and division by zero
			if (1e-160 < lensq && lensq <= 1)
				return p / std::sqrt(lensq);
		}
	}
};

inline double dot(const Vector3& u, const Vector3& v) {
	return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline Vector3 cross(const Vector3& u, const Vector3& v) {
	return Vector3(u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x());
}

inline Vector3 operator*(double scalar, const Vector3& vec) {
	return vec * scalar;
}

// Returns an evenly distrubted random unit vector in the same hemisphere as the given normal vector.
inline Vector3 randomOnHemisphere(const Vector3& normal) {
	Vector3 randomOnSphere = Vector3::randomUnitVector();
	if (dot(randomOnSphere, normal) >= 0.0) // In the same hemisphere as the normal
		return randomOnSphere;
	else
		return -randomOnSphere;
}