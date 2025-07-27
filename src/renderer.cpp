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
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Simple Pixels", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glViewport(0, 0, windowWidth, windowHeight);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);

        // Draw each pixel
        for (int y = 0; y < windowHeight; y++) {
            for (int x = 0; x < windowWidth; x++) {
                // Simple color calculation
                float red = (float)x / windowWidth;      // Red increases left to right
                float green = (float)y / windowHeight;   // Green increases bottom to top  
                float blue = 0.0f;                       // No blue

                // Set pixel color
                glColor3f(red, green, blue);

                // Draw the pixel
                float glX = (x / (float)windowWidth) * 2.0f - 1.0f;
                float glY = (y / (float)windowHeight) * 2.0f - 1.0f;
                glVertex2f(glX, glY);
            }
        }

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}