#include "raycasting.h"

// Player position
float px;
float py;
float pxDelta;
float pyDelta;
float pAngle;

// Map size
int mapX = 8;
int mapY = 8;
int mapSize = 64;
int map[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 1, 1, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    glOrtho(0, 1024, 512, 0, -1, 1);

    px = 220;
    py = 220;
    pxDelta = cos(pAngle) * 5;
    pyDelta = sin(pAngle) * 5;
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap();
    drawRays();
    drawPlayer();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void processInput(GLFWwindow* window) {
    int offsetX, offsetY;

    pxDelta < 0 ? offsetX = -20 : offsetX = 20;
    pyDelta < 0 ? offsetY = -20 : offsetY = 20;

    const int ipx = px / 64, ipy = py / 64;
    const int ipxAddOffsetX = (px + offsetX) / 64, ipyAddOffsetY = (py + offsetY) / 64;
    int ipxSubOffsetX = (px - offsetX) / 64, ipySubOffsetY = (py - offsetY) / 64;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (map[ipy * mapX + ipxAddOffsetX] == 0)
            px += pxDelta / 3;
        if (map[ipx + mapX * ipyAddOffsetY] == 0)
            py += pyDelta / 3;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        pAngle -= 0.02;

        if (pAngle < 0)
            pAngle += 2 * M_PI;

        pxDelta = cos(pAngle) * 5;
        pyDelta = sin(pAngle) * 5;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (map[ipy * mapX + ipxSubOffsetX] == 0)
            px -= pxDelta / 3;
        if (map[ipx + mapX * ipySubOffsetY] == 0)
            py -= pyDelta / 3;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        pAngle += 0.02;

        if (pAngle > 2 * M_PI)
            pAngle -= 2 * M_PI;

        pxDelta = cos(pAngle) * 5;
        pyDelta = sin(pAngle) * 5;
    }
}

float dist(float x1, float y1, float x2, float y2, float deg) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

