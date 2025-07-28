#include "Hittable.h"
#include "ray.h"

class Sphere : Hittable {

public:

	Vector3 center;
	double radius;

	Sphere(Vector3 center, double radius) : center(center), radius(std::fmax(0, radius)) {}

	bool hit(const ray& r, double rayTMin, double rayTMax, hitRecord& rec) const {
        Vector3 originToCenter = center - r.origin;
        double a = r.dir.length_squared();
        double h = dot(r.dir, originToCenter);
        double c = originToCenter.length_squared() - radius * radius;
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

        rec.t = root;
        rec.p = r.at(rec.t);
        Vector3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
	}

};