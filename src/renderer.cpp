#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create window
    int windowWidth = 400;
    int windowHeight = 400;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Static Image", NULL, NULL);

    glfwMakeContextCurrent(window);

    // Render the image ONCE
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    // Draw each pixel
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            float u = (float)x / (windowWidth);
            float v = (float)y / (windowHeight);
            float b = 0.0f;

            float r = u;
            float g = v;

            // Set pixel color
            glColor3f(r, g, b);

            // Draw the pixel
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