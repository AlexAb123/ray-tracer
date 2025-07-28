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

	double dot(const vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	vec3 cross(const vec3& other) const {
		return vec3(y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
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

inline vec3 operator*(double scalar, const vec3& vec) {
	return vec * scalar;
}