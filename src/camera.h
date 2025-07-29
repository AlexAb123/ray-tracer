#include "hittable.h"

class Camera {
public:
    double aspectRatio = 1.0; // Ratio of image width over height
    int    imageWidth = 100;  // Rendered image width in pixel count
    void   render(const Hittable& world);

private:
    int     imageHeight;   // Rendered image height
    Vector3 center;        // Camera center
    Vector3 pixel00Center; // Location of pixel 0, 0
    Vector3 pixelDeltaU;   // Offset to pixel to the right
    Vector3 pixelDeltaV;   // Offset to pixel below

    void initialize();
    Vector3 rayColor(const Ray& r, const Hittable& world) const;
};
