#pragma once

#include <cmath>

class Vector3 {

public:

	double x, y, z;

	Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
	Vector3(double value) : x(value), y(value), z(value) {}

	Vector3 operator+(const Vector3& other) const {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3& operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3 operator-(const Vector3& other) const {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 operator-() const {
		return Vector3(-x, -y, -z);
	}

	Vector3& operator-=(const Vector3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3 operator*(const double scalar) const {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3& operator*=(const double scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3 operator/(const double scalar) const {
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	Vector3& operator/=(const double scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	double length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	double length_squared() const {
		return x * x + y * y + z * z;
	}

	// Normalizes vectors with non-zero length.
	Vector3 normalize() const {
		return *this / length();
	}

};

inline double dot(const Vector3& u, const Vector3& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline Vector3 cross(const Vector3& u, const Vector3& v) {
	return Vector3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}

inline Vector3 operator*(double scalar, const Vector3& vec) {
	return vec * scalar;
}