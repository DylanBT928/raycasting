#include "draw.h"

// Degrees to radians
float DR = 0.0174533;

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
    float rayX = 0, rayY = 0, offsetX = 0, offsetY = 0, disT = 0;
    float rayAngle = pAngle - DR * 30;

    if (rayAngle < 0)
        rayAngle += 2 * M_PI;
    if (rayAngle > 2 * M_PI)
        rayAngle -= 2 * M_PI;

    for (int r = 0; r < 60; r++) {
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

        // Vertical wall hit
        if (disV < disH) {
            rayX = vx;
            rayY = vy;
            disT = disV;
            glColor3f(0.9, 0, 0);
        }
        // Horizontal wall hit
        else if (disH < disV) {
            rayX = hx;
            rayY = hy;
            disT = disH;
            glColor3f(0.7, 0, 0);
        }

        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2f(px, py);
        glVertex2f(rayX, rayY);
        glEnd();

        drawWalls(disT, rayAngle, r);

        rayAngle += DR;
        if (rayAngle < 0)
            rayAngle += 2 * M_PI;
        if (rayAngle > 2 * M_PI)
            rayAngle -= 2 * M_PI;
    }
}

void drawWalls(float disT, const float rayAngle, const float r) {
    float lineHeight = (mapSize * 512) / disT;
    float sideRays = pAngle - rayAngle;

    // Fix fisheye effect
    if (sideRays < 0)
        sideRays += 2 * M_PI;
    if (sideRays > 2 * M_PI)
        sideRays -= 2 * M_PI;
    disT *= cos(sideRays);

    // Line height
    if (lineHeight > 512)
        lineHeight = 512;

    const float lineOffset = 256 - lineHeight / 2;

    glLineWidth(20);
    glBegin(GL_LINES);
    glVertex2f(r * 8 + 530, lineOffset);
    glVertex2f(r * 8 + 530, lineHeight + lineOffset);
    glEnd();
}
