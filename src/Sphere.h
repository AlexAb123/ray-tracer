#include "hittable.h"
#include "ray.h"

class Sphere : Hittable {

private:
    Vector3 m_center;
    double m_radius;

public:

	Sphere(Vector3 center, double radius) : m_center(center), m_radius(std::fmax(0, radius)) {}

    const Vector3& center() const { return m_center; }
    double radius() const { return m_radius; }

    bool hit(const Ray& r, double rayTMin, double rayTMax, HitRecord& record) const {
        Vector3 originToCenter = m_center - r.origin();
        double a = r.dir().length_squared();
        double h = dot(r.dir(), originToCenter);
        double c = originToCenter.length_squared() - m_radius * m_radius;
        double discriminant = h * h - a * c;

        if (discriminant < 0)
            return false;

        double sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (h - sqrtd) / a;
        if (root <= rayTMin || rayTMax <= root) {
            root = (h + sqrtd) / a;
            if (root <= rayTMin || rayTMax <= root)
                return false;
        }

        record.setT(root);
        record.setPoint(r.at(record.t()));
        Vector3 outward_normal = (record.point() - m_center) / m_radius;
        record.setFaceNormal(r, outward_normal);

        return true;
	}
};