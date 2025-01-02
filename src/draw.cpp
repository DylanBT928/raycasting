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
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(px, py);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(px, py);
    glVertex2f(px + pxDelta * 5, py + pyDelta * 5);
    glEnd();
}

void drawRays() {
    float rayX = 0, rayY = 0, offsetX = 0, offsetY = 0;
    const float rayAngle = pAngle;

    for (int r = 0; r < 1; r++) {
        // CHECK HORIZONTAL LINES
        int depthOfField = 0;
        const float aTan = -1 / tan(rayAngle);
        float disH = INT_MAX;
        float hx = px;
        float hy = py;

        // Looking up
        if (rayAngle > M_PI) {
            rayY = (static_cast<int>(py)>>6<<6) - 0.0001;
            rayX = (py - rayY) * aTan + px;
            offsetY = -64;
            offsetX = -offsetY * aTan;
        }

        // Looking down
        if (rayAngle < M_PI) {
            rayY = (static_cast<int>(py)>>6<<6) + 64;
            rayX = (py - rayY) * aTan + px;
            offsetY = 64;
            offsetX = -offsetY * aTan;
        }

        // Looking directly left or right
        if (rayAngle == 0 || rayAngle == M_PI) {
            rayX = px;
            rayY = py;
            depthOfField = 8;
        }

        while (depthOfField < 8) {
            const int mx = static_cast<int>(rayX) >> 6;
            const int my = static_cast<int>(rayY) >> 6;

            // Hit wall
            if (const int mapPosition = my * mapX + mx; mapPosition > 0 && mapPosition < mapX * mapY && map[mapPosition] == 1) {
                hx = rayX;
                hy = rayY;
                disH = dist(px, py, hx, hy, rayAngle);
                depthOfField = 8;
            }
            // Next line
            else {
                rayX += offsetX;
                rayY += offsetY;
                depthOfField += 1;
            }
        }

        // CHECK VERTICAL LINES
        depthOfField = 0;
        const float aTanNeg = -tan(rayAngle);
        float disV = INT_MAX;
        float vx = px;
        float vy = py;

        // Looking left
        if (rayAngle > M_PI_2 && rayAngle < 3 * M_PI_2) {
            rayX = (static_cast<int>(px)>>6<<6) - 0.0001;
            rayY = (px - rayX) * aTanNeg + py;
            offsetX = -64;
            offsetY = -offsetX * aTanNeg;
        }

        // Looking right
        if (rayAngle < M_PI_2 || rayAngle > 3 * M_PI_2) {
            rayX = (static_cast<int>(px)>>6<<6) + 64;
            rayY = (px - rayX) * aTanNeg + py;
            offsetX = 64;
            offsetY = -offsetX * aTanNeg;
        }

        // Looking directly up or down
        if (rayAngle == 0 || rayAngle == M_PI) {
            rayX = px;
            rayY = py;
            depthOfField = 8;
        }

        while (depthOfField < 8) {
            const int mx = static_cast<int>(rayX) >> 6;
            const int my = static_cast<int>(rayY) >> 6;

            // Hit wall
            if (const int mapPosition = my * mapX + mx; mapPosition > 0 && mapPosition < mapX * mapY && map[mapPosition] == 1) {
                vx = rayX;
                vy = rayY;
                disV = dist(px, py, vx, vy, rayAngle);
                depthOfField = 8;
            }
            // Next line
            else {
                rayX += offsetX;
                rayY += offsetY;
                depthOfField += 1;
            }
        }

        if (disV < disH) {
            rayX = vx;
            rayY = vy;
        }
        else if (disH < disV) {
            rayX = hx;
            rayY = hy;
        }

        glColor3f(1, 0, 0);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2f(px, py);
        glVertex2f(rayX, rayY);
        glEnd();
    }
}
