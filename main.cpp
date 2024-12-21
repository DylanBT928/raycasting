#include <cstdio>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void display(GLFWwindow* window);
void init();

constexpr unsigned int SCREEN_WIDTH = 1024;
constexpr unsigned int SCREEN_HEIGHT = 512;

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting", nullptr, nullptr);
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

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
}
