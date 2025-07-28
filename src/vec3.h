#pragma once

#include <cmath>

class vec3 {

public:

	double x, y, z;

	vec3(double x, double y, double z) : x(x), y(y), z(z) {}
	vec3(double value) : x(value), y(value), z(value) {}

	vec3 operator+(const vec3& other) const {
		return vec3(x + other.x, y + other.y, z + other.z);
	}

	vec3& operator+=(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3 operator-(const vec3& other) const {
		return vec3(x - other.x, y - other.y, z - other.z);
	}

	vec3& operator-=(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3 operator*(const double scalar) const {
		return vec3(x * scalar, y * scalar, z * scalar);
	}

	vec3& operator*=(const double scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	vec3 operator/(const double scalar) const {
		return vec3(x / scalar, y / scalar, z / scalar);
	}

	vec3& operator/=(const double scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	double length() const {
		return sqrt(x * x + y * y + z * z);
	}

	double length_squared() const {
		return x * x + y * y + z * z;
	}

	// Normalizes vectors with non-zero length.
	vec3 normalize() const {
		return *this / length();
	}

};

inline double dot(const vec3& u, const vec3& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}

inline vec3 operator*(double scalar, const vec3& vec) {
	return vec * scalar;
}