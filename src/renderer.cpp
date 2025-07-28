#include <GLFW/glfw3.h>
#include <iostream>
#include "vec3.h"
#include "ray.h"

bool hitSphere(const vec3& sphereCenter, const double sphereRadius, const ray& r) {
    vec3 originToCenter = r.origin - sphereCenter;
    double a = dot(r.dir, r.dir);
    double b = dot(-2.0 * r.dir, originToCenter);
    double c = dot(originToCenter, originToCenter) - (sphereRadius * sphereRadius);
    double discriminant = (b * b) - (4 * a * c);
    return discriminant >= 0;
}

vec3 rayColor(const ray& r) {

    if (hitSphere(vec3(0, 0, 2), 1.0, r)) {
        return vec3(1, 0, 0);
    }

    vec3 unit = r.dir.normalize();
    auto a = 0.5 * (unit.y + 1.0);
    return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
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
    vec3 cameraCenter = vec3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewportU = vec3(viewportWidth, 0, 0);
    vec3 viewportV = vec3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixelDeltaU = viewportU / imageWidth;
    vec3 pixelDeltaV = viewportV / imageHeight;

    vec3 viewportTopLeft = cameraCenter - vec3(0, 0, focalLength) - (viewportU / 2.0) - (viewportV / 2.0);
    vec3 pixel00Center = viewportTopLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Create window
    GLFWwindow* window = glfwCreateWindow(imageWidth, imageHeight, "renderer", NULL, NULL);

    glfwMakeContextCurrent(window);

    // Render the image ONCE
    glViewport(0, 0, imageWidth, imageHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    // Draw each pixel
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            double u = (double)x / (imageWidth);
            double v = (double)y / (imageHeight);

            vec3 pixelCenter = pixel00Center + (x * pixelDeltaU) + (y * pixelDeltaV);
            vec3 rayDirection = pixelCenter - cameraCenter;

            ray r(cameraCenter, rayDirection);

            vec3 pixelColor = rayColor(r);

            // Set pixel vec3 and draw pixel
            glColor3f((float)pixelColor.x, (float)pixelColor.y, (float)pixelColor.z);
            float glU = float((u) * 2.0f - 1.0f);
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