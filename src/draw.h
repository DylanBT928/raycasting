#ifndef DRAW_H
#define DRAW_H

#include "raycasting.h"

// Degrees to radians
extern float DR;

void drawMap();
void drawPlayer();
void drawRays();
void drawWalls(float disT, float rayAngle, float r);

#endif //DRAW_H
