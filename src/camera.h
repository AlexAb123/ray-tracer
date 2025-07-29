#pragma once
#include "hittable.h"

class Camera {
public:

    void render(const Hittable& world);
    void setAspectRatio(double aspectRatio) { m_aspectRatio = aspectRatio; }
    void setImageWidth(int imageWidth) { m_imageWidth = imageWidth; }
    void setSamplesPerPixel(int samplesPerPixel) { m_samplesPerPixel = samplesPerPixel; }

private:
    double  m_aspectRatio = 16.0 / 9.0; // Ratio of image width over height
    int     m_imageWidth = 1600;;       // Rendered image width in pixel count
    int     m_imageHeight = 900;        // Rendered image height
    int     m_samplesPerPixel = 10;     // Count of random samples for each pixel
    double m_pixelSamplesScale = 0.1;         // Color scale factor for a sum of pixel samples
    Vector3 m_center;                   // Camera center
    Vector3 m_pixel00Center;            // Location of pixel 0, 0
    Vector3 m_pixelDeltaU;              // World space offset to pixel to the right
    Vector3 m_pixelDeltaV;              // World space offset to pixel below

    void initialize();
    Vector3 rayColor(const Ray& r, const Hittable& world) const;
    Ray getRay(int x, int y) const;
    static Vector3 sampleSquare();
};
