#pragma once
#include "hittable.h"

class Camera {
public:

	void render(const Hittable& world);
	void setAspectRatio(double aspectRatio) { m_aspectRatio = aspectRatio; }
	void setImageWidth(int imageWidth) { m_imageWidth = imageWidth; }
	void setSamplesPerPixel(int samplesPerPixel) { m_samplesPerPixel = samplesPerPixel; }
	void setMaxBounces(int maxBounces) { m_maxBounces = maxBounces; }
	void setVFov(double vFov) { m_vFov = vFov; }
	void setLookFrom(const Vector3& lookFrom) { m_lookFrom = lookFrom; }
	void setLookAt(const Vector3& lookAt) { m_lookAt = lookAt; }
	void setUp(const Vector3& up) { m_up = up; }
	void setDefocusAngle(double defocusAngle) { m_defocusAngle = defocusAngle; }
	void setFocusDist(double focusDist) { m_focusDist = focusDist; }

private:
	double  m_aspectRatio = 16.0 / 9.0;    // Ratio of image width over height
	int     m_imageWidth = 1600;;          // Rendered image width in pixel count
	int     m_imageHeight = 900;           // Rendered image height
	int     m_samplesPerPixel = 10;        // Count of random samples for each pixel
	double  m_pixelSamplesScale = 0.1;     // Color scale factor for a sum of pixel samples
	int     m_maxBounces = 10;             // Max amount of ray bounces
	Vector3 m_center;                      // Camera center
	Vector3 m_pixel00Center;               // Location of pixel 0, 0
	Vector3 m_pixelDeltaU;                 // World space offset to pixel to the right
	Vector3 m_pixelDeltaV;                 // World space offset to pixel below
	double  m_vFov = 90;				   // Vertical view angle (field of view)
	Vector3 m_lookFrom = Vector3(0, 0, 0); // Point camera is looking from
	Vector3 m_lookAt = Vector3(0, 0, -1);  // Point camera is looking at
	Vector3 m_up = Vector3(0, 1, 0);	   // Camera-relative "up" direction
	Vector3 m_u, m_v, m_w;                 // Camera frame basis vectors
	double  m_defocusAngle = 10;		   // Variation angle of rays through each pixel
	double  m_focusDist = 3.4;			   // Distance from camera lookfrom point to plane of perfect focus
	Vector3 m_defocusDiskU;				   // Defocus disk horizontal radius
	Vector3 m_defocusDiskV;				   // Defocus disk vertical radius

	void initialize();
	Vector3 rayColor(const Ray& r, const Hittable& world, const int bounces) const;
	Ray getRay(int x, int y) const;
	static Vector3 sampleSquare();
	Vector3 defocusDiskSample() const;

};
