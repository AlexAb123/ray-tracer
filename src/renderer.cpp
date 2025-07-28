#include <GLFW/glfw3.h>
#include <iostream>
#include "vec3.h"
#include "ray.h"

vec3 rayColor(ray& r) {
    return vec3(r.dir.length() / 10.0);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Image and aspect ratio
    float idealAspectRatio = 16.0 / 9.0;
    int imageWidth = 800;
    int imageHeight = imageWidth / idealAspectRatio;
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;
    float aspectRatio = (float)imageWidth / imageHeight;

    // Camera
    float focalLength = 1.0f;
    float viewportHeight = 2.0f;
    float viewportWidth = viewportHeight * aspectRatio;
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
    GLFWwindow* window = glfwCreateWindow(imageWidth, imageHeight, "Static Image", NULL, NULL);

    glfwMakeContextCurrent(window);

    // Render the image ONCE
    glViewport(0, 0, imageWidth, imageHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    // Draw each pixel
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            float u = (float)x / (imageWidth);
            float v = (float)y / (imageHeight);

            vec3 pixelCenter = pixel00Center + (x * pixelDeltaU) + (y * pixelDeltaV);
            vec3 rayDirection = pixelCenter - cameraCenter;

            ray r(cameraCenter, rayDirection);

            vec3 pixelColor = rayColor(r);

            // Set pixel vec3 and draw pixel
            glColor3f(pixelColor.x, pixelColor.y, pixelColor.z);
            float glU = (u) * 2.0f - 1.0f;
            float glV = -1.0f * (v * 2.0f - 1.0f);
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