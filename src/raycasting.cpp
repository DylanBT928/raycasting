#include "raycasting.h"

// Player position
float px = 300;
float py = 300;

// Map size
int mapX = 8;
int mapY = 8;
int mapSize = 64;
int map[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 1, 1, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    glOrtho(0, 1024, 512, 0, -1, 1);
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap();
    drawPlayer();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        py -= 2;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        px -= 2;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        py += 2;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        px += 2;
    }
}
