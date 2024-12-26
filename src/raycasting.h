#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <GLFW/glfw3.h>
#include "draw.h"

// Player position
extern float px;
extern float py;

// Map size
extern int mapX;
extern int mapY;
extern int mapSize;
extern int map[];

void init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void display(GLFWwindow* window);
void processInput(GLFWwindow* window);

#endif //RAYCASTING_H
