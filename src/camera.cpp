#include <GLFW/glfw3.h>
#include "camera.h"

void Camera::initialize()
{

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
    Vector3 center = Vector3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vector3 viewportU = Vector3(viewportWidth, 0, 0);
    Vector3 viewportV = Vector3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vector3 pixelDeltaU = viewportU / imageWidth;
    Vector3 pixelDeltaV = viewportV / imageHeight;

    Vector3 viewportTopLeft = center - Vector3(0, 0, focalLength) - (viewportU / 2.0) - (viewportV / 2.0);
    Vector3 pixel00Center = viewportTopLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
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
            Vector3 rayDir = pixelCenter - center;

            Ray r(center, rayDir);

            Vector3 pixelColor = rayColor(r, world);

            // Set pixel Vector3 and draw pixel
            glColor3f((float)pixelColor.x(), (float)pixelColor.y(), (float)pixelColor.z());
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



Vector3 Camera::rayColor(const Ray& r, const Hittable& world) const
{
    HitRecord rec;

    if (world.hit(r, Interval(0, INF), rec)) {
        return 0.5 * (rec.normal() + Vector3(1, 1, 1));
    }

    // If no hit, display a background color
    Vector3 unit = r.dir().normalize();
    auto a = 0.5 * (unit.y() + 1.0);
    return (1.0 - a) * Vector3(1.0, 1.0, 1.0) + a * Vector3(0.5, 0.7, 1.0);
}
