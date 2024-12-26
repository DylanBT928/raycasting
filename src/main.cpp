#include "raycasting.h"

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1024, 512, "Raycasting", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    init();

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        // Handle input
        processInput(window);

        // Handle display and rendering
        display(window);
    }

    glfwTerminate();
    return 0;
}
