#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <GLFW/glfw3.h>
#include "draw.h"
#include <cmath>
#include <climits>

// Player position
extern float px;
extern float py;
extern float pxDelta;
extern float pyDelta;
extern float pAngle;

// Map size
extern int mapX;
extern int mapY;
extern int mapSize;
extern int map[];

void init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void display(GLFWwindow* window);
void processInput(GLFWwindow* window);
float dist(float x1, float y1, float x2, float y2, float deg);

#endif //RAYCASTING_H
