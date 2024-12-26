#include "draw.h"

void drawMap() {
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            const int deltaX = x * mapSize;
            const int deltaY = y * mapSize;
            map[y * mapX + x] == 1 ? glColor3f(1, 1, 1) : glColor3f(0, 0, 0);
            glBegin(GL_QUADS);
            glVertex2d(deltaX + 0.5, deltaY + 0.5);
            glVertex2d(deltaX + 0.5, deltaY + mapSize - 0.5);
            glVertex2d(deltaX + mapSize - 0.5, deltaY + mapSize - 0.5);
            glVertex2d(deltaX + mapSize - 0.5, deltaY + 0.5);
            glEnd();
        }
    }
}

void drawPlayer() {
    glColor3f(1, 1, 0);
    glPointSize(15);
    glBegin(GL_POINTS);
    glVertex2f(px, py);
    glEnd();
}
