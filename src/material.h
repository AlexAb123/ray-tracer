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