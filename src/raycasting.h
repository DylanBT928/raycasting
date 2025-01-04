#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <GLFW/glfw3.h>
#include <cmath>
#include <climits>
#include "draw.h"

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
float dist(const float x1, const float y1, const float x2, const float y2);

#endif //RAYCASTING_H
