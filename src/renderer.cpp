#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"

// Returns t value of first point of intersection with Sphere. -1.0 if no intersection.
double hitSphere(const Vector3& sphereCenter, const double sphereRadius, const Ray& r) {
    Vector3 originToCenter = sphereCenter - r.origin;
    double a = r.dir.length_squared();
    double h = dot(r.dir, originToCenter);
    double c = originToCenter.length_squared() - sphereRadius * sphereRadius;
    double discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (h - std::sqrt(discriminant)) / a;
    }
}

Vector3 rayColor(const Ray& r) {

    Vector3 sphereCenter = Vector3(0, 0, -1);
    double sphereRadius = 0.5;

    double t = hitSphere(sphereCenter, sphereRadius, r);
    if (t > 0.0) {
        Vector3 normal = (r.at(t) - sphereCenter).normalize();
        return 0.5 * (normal + Vector3(1));
    }

    Vector3 unit = r.dir.normalize();
    auto a = 0.5 * (unit.y + 1.0);
    return (1.0 - a) * Vector3(1.0, 1.0, 1.0) + a * Vector3(0.5, 0.7, 1.0);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Image and aspect ratio
    double idealAspectRatio = 16.0 / 9.0;
    int imageWidth = 800;
    int imageHeight = int(imageWidth / idealAspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;
    double aspectRatio = (double)imageWidth / imageHeight;

    // Camera
    double focalLength = 1.0f;
    double viewportHeight = 2.0f;
    double viewportWidth = viewportHeight * aspectRatio;
    Vector3 cameraCenter = Vector3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vector3 viewportU = Vector3(viewportWidth, 0, 0);
    Vector3 viewportV = Vector3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vector3 pixelDeltaU = viewportU / imageWidth;
    Vector3 pixelDeltaV = viewportV / imageHeight;

    Vector3 viewportTopLeft = cameraCenter - Vector3(0, 0, focalLength) - (viewportU / 2.0) - (viewportV / 2.0);
    Vector3 pixel00Center = viewportTopLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Create window
    GLFWwindow* window = glfwCreateWindow(imageWidth, imageHeight, "Renderer", NULL, NULL);

    glfwMakeContextCurrent(window);

    // Render the image ONCE
    glViewport(0, 0, imageWidth, imageHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    // Draw each pixel
     for (int x = 0; x < imageWidth; x++) {
        for (int y = 0; y < imageHeight; y++) {
            double u = (double)x / (imageWidth);
            double v = (double)y / (imageHeight);

            Vector3 pixelCenter = pixel00Center + (x * pixelDeltaU) + (y * pixelDeltaV);
            Vector3 rayDir = pixelCenter - cameraCenter;

            Ray r(cameraCenter, rayDir);

            Vector3 pixelColor = rayColor(r);

            // Set pixel Vector3 and draw pixel
            glColor3f((float)pixelColor.x, (float)pixelColor.y, (float)pixelColor.z);
            float glU = float(u * 2.0f - 1.0f);
            float glV = float(-1.0f * (v * 2.0f - 1.0f));
            glVertex2f(glU, glV);
        }
    }

    glEnd();
    glfwSwapBuffers(window);

    // Keep window open until user closes it
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();  // Just check for close button - no redrawing
    }

    glfwTerminate();
}