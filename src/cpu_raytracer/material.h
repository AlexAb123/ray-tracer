#pragma once

#include "hittable.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vector3& attenuation, Ray& scattered) const {
        return false;
    }
private:

};

class Lambertian : public Material {
public:
    Lambertian(const Vector3& albedo) : m_albedo(albedo) {}

    bool scatter(const Ray& rIn, const HitRecord& rec, Vector3& attenuation, Ray& scattered) const override {
        Vector3 scatterDirection = rec.normal() + randomUnitVector();

        // Catch degenerate scatter directions
        if (scatterDirection.nearZero())
            scatterDirection = rec.normal();

        scattered = Ray(rec.point(), scatterDirection);
        attenuation = m_albedo;
        return true;
    }

private:
    Vector3 m_albedo;
};

class Metal : public Material {
public:
    Metal(const Vector3& albedo, double fuzz) : m_albedo(albedo), m_fuzz(std::min(fuzz, 1.0)) {}

    bool scatter(const Ray& rIn, const HitRecord& rec, Vector3& attenuation, Ray& scattered) const override {
        Vector3 reflected = reflect(rIn.direction(), rec.normal());
        reflected = reflected.normalize() + (m_fuzz * randomUnitVector());
        scattered = Ray(rec.point(), reflected);
        attenuation = m_albedo;
        return (dot(scattered.direction(), rec.normal()) > 0);
    }

private:
    Vector3 m_albedo;
    double m_fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(double refractionIndex) : m_refractionIndex(refractionIndex) {}

    bool scatter(const Ray& rIn, const HitRecord& rec, Vector3& attenuation, Ray& scattered) const override {
        attenuation = Vector3(1.0, 1.0, 1.0);
        double ri = rec.frontFace() ? (1.0 / m_refractionIndex) : m_refractionIndex; // Use reciprocal of refraction index when entering material

        Vector3 unitDirection = rIn.direction().normalize();

        double cosTheta = std::fmin(dot(-unitDirection, rec.normal()), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = ri * sinTheta > 1.0;
        Vector3 direction;

        if (cannotRefract || reflectance(cosTheta, ri) > randomDouble())
            direction = reflect(unitDirection, rec.normal());
        else
            direction = refract(unitDirection, rec.normal(), ri);

        scattered = Ray(rec.point(), direction);
        return true;
    }

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double m_refractionIndex;

    static double reflectance(double cosine, double refractionIndex) {
        // Use Schlick's approximation for reflectance.
        double r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};