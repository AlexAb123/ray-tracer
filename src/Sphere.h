#pragma once

#include "hittable.h"
#include "ray.h"

class Sphere : public Hittable {

private:
    Vector3 m_center;
    double m_radius;
    shared_ptr<Material> m_material;

public:

	Sphere(const Vector3 center, double radius, const shared_ptr<Material> material)
        : m_center(center), m_radius(std::fmax(0, radius)), m_material(material) {}

    const Vector3& center() const { return m_center; }
    double radius() const { return m_radius; }

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override {
        Vector3 originToCenter = m_center - r.origin();
        double a = r.direction().lengthSquared();
        double h = dot(r.direction(), originToCenter);
        double c = originToCenter.lengthSquared() - m_radius * m_radius;
        double discriminant = h * h - a * c;

        if (discriminant < 0)
            return false;

        double sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (h - sqrtd) / a;
        if (!rayT.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!rayT.surrounds(root))
                return false;
        }

        rec.setT(root);
        rec.setPoint(r.at(rec.t()));
        Vector3 outward_normal = (rec.point() - m_center) / m_radius; // Unit vector
        rec.setFaceNormal(r, outward_normal);
        rec.setMaterial(m_material);

        return true;
	}
};