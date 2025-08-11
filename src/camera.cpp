#include <GLFW/glfw3.h>
#include "camera.h"
#include "material.h"
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void Camera::initialize()
{
    // Image and aspect ratio
    m_imageHeight = int(m_imageWidth / m_aspectRatio);
    m_imageHeight = (m_imageHeight < 1) ? 1 : m_imageHeight;

    m_pixelSamplesScale = 1.0 / m_samplesPerPixel;

    m_center = m_lookFrom;

    // Camera
    double theta = degreesToRadians(m_vFov); // Vertical field of view in degrees
    double h = std::tan(theta / 2); // Half of the viewport height per unit focal length
    double viewportHeight = 2 * h * m_focusDist;
    double viewportWidth = viewportHeight * (double)m_imageWidth / m_imageHeight;

    // Calculate the u,v,w orthonormal basis vectors for the camera coordinate frame.
    m_w = (m_lookFrom - m_lookAt).normalize(); // Backward
    m_u = cross(m_up, m_w).normalize(); // Right 
    m_v = cross(m_w, m_u); // Up

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vector3 viewportU = viewportWidth * m_u;
    Vector3 viewportV = viewportHeight * -m_v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    m_pixelDeltaU = viewportU / m_imageWidth;
    m_pixelDeltaV = viewportV / m_imageHeight;

    Vector3 viewportTopLeft = m_center - (m_focusDist * m_w) - (viewportU / 2.0) - (viewportV / 2.0);
    m_pixel00Center = viewportTopLeft + 0.5 * (m_pixelDeltaU + m_pixelDeltaV);

    // Calculate the camera defocus disk basis vectors.
    double defocusRadius = m_focusDist * std::tan(degreesToRadians(m_defocusAngle / 2));
    m_defocusDiskU = m_u * defocusRadius;
    m_defocusDiskV = m_v * defocusRadius;
}

void Camera::render(const Hittable& world)
{
    initialize();

    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(m_imageWidth, m_imageHeight, "Renderer", NULL, NULL);

    glfwMakeContextCurrent(window);

    // Render the image ONCE
    glViewport(0, 0, m_imageWidth, m_imageHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    std::vector<unsigned char> pixels(m_imageWidth * m_imageHeight * 3);

    // Draw each pixel
    for (int x = 0; x < m_imageWidth; x++) {
        std::clog << "\r% Completed: " << std::round(1000.0 * x / (m_imageWidth - 1)) / 10.0 << std::flush;
        for (int y = 0; y < m_imageHeight; y++) {

            Vector3 pixelColor(0,0,0);
            for (int sample = 0; sample < m_samplesPerPixel; sample++) {
                Ray r = getRay(x, y);
                pixelColor += rayColor(r, world, 0);
            }
            pixelColor *= m_pixelSamplesScale;
            pixelColor = Vector3(linearToGamma(pixelColor.x()), linearToGamma(pixelColor.y()), linearToGamma(pixelColor.z()));

            // Set pixel Vector3 and draw pixel
            glColor3f((float)pixelColor.x(), (float)pixelColor.y(), (float)pixelColor.z());
            double u = (double)x / (m_imageWidth);
            double v = (double)y / (m_imageHeight);
            float glU = float(u * 2.0f - 1.0f);
            float glV = float(-1.0f * (v * 2.0f - 1.0f));           glVertex2f(glU, glV);

            auto clamp01 = [](double v) { return v < 0.0 ? 0.0 : (v > 0.999 ? 0.999 : v); };


            // Store into pixel buffer (no manual flip here)
            int index = (y * m_imageWidth + x) * 3;
            pixels[index + 0] = (unsigned char)(255 * pixelColor.x());
            pixels[index + 1] = (unsigned char)(255 * pixelColor.y());
            pixels[index + 2] = (unsigned char)(255 * pixelColor.z());

        }
    }
    std::clog << "\r% Completed: 100.0\n";

    stbi_write_png("render.png", m_imageWidth, m_imageHeight, 3, pixels.data(), m_imageWidth * 3);

    glEnd();
    glfwSwapBuffers(window);

    // Keep window open until user closes it
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();  // Just check for close button - no redrawing
    }

    glfwTerminate();
}

Vector3 Camera::rayColor(const Ray& r, const Hittable& world, const int bounces) const
{
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (bounces >= m_maxBounces) {
        return Vector3(0, 0, 0);
    }
    
    HitRecord rec;

    if (world.hit(r, Interval(0.001, INF), rec)) {
        Ray scattered;
        Vector3 attenuation;
        if (rec.material()->scatter(r, rec, attenuation, scattered))
            return attenuation * rayColor(scattered, world, bounces + 1);
        return Vector3(0, 0, 0);
    }

    // If no hit, display a background color
    Vector3 unit = r.direction().normalize();
    auto a = 0.5 * (unit.y() + 1.0);
    return (1.0 - a) * Vector3(1.0, 1.0, 1.0) + a * Vector3(0.5, 0.7, 1.0);
}

// Construct a camera ray originating from the defocus disk and directed at a randomly
// sampled point around the pixel location x, y.
Ray Camera::getRay(int x, int y) const
{
    Vector3 offset = Camera::sampleSquare();
    Vector3 pixelSample = m_pixel00Center
        + ((x + offset.x()) * m_pixelDeltaU)
        + ((y + offset.y()) * m_pixelDeltaV);

    Vector3 rayOrigin = (m_defocusAngle <= 0) ? m_center : defocusDiskSample();
    Vector3 rayDir = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDir);
}

// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
Vector3 Camera::sampleSquare() {
    return Vector3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}

// Returns a random point in the camera defocus disk.
Vector3 Camera::defocusDiskSample() const {
    Vector3 v = randomInUnitDisk();
    return m_center + (v.x() * m_defocusDiskU) + (v.y() * m_defocusDiskV);
}