#pragma once

#include <cmath>

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

	Vector3 operator*(const double scalar) const {
		return Vector3(m_x * scalar, m_y * scalar, m_z * scalar);
	}

	Vector3& operator*=(const double scalar) {
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		return *this;
	}

	Vector3 operator/(const double scalar) const {
		return Vector3(m_x / scalar, m_y / scalar, m_z / scalar);
	}

	Vector3& operator/=(const double scalar) {
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		return *this;
	}

	double length() const {
		return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	double length_squared() const {
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}

	// Normalizes vectors with non-zero length.
	Vector3 normalize() const {
		return *this / length();
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