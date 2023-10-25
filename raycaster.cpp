#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2

float px, py, pdx, pdy, pa; //player position

void drawPlayer(){
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px,py);
    glEnd();
    
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + pdx * 5, py + pdy * 5);
    glEnd();
}

int mapX = 8, mapY = 8, mapS = 64;
int map[] = 
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

void drawMap2D(){
    int x, y, xo, yo;
    for(y = 0; y < mapY; y++){
        for(x = 0; x < mapX; x++){
            if(map[y * mapX + x] == 1){
                glColor3f(1, 1, 1);
            } else {
                glColor3f(0, 0, 0);
            }
            
            xo = x * mapS;
            yo = y * mapS;
            glBegin(GL_QUADS);
            glVertex2i(xo + 1, yo + 1);
            glVertex2i(xo + 1, yo + mapS - 1);
            glVertex2i(xo + mapS - 1, yo + mapS - 1);
            glVertex2i(xo + mapS - 1, yo + 1);
            glEnd();
        }
    }
}

void drawRays2D(){
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo;
    ra = pa;
    for(r = 0; r < 1; r++){
        //Check horizontal lines
        dof = 0;
        float aTan = -1 / tan(ra);
        if(ra > PI){
            //Looking up
            ry = (((int)py>>6)<<6) - 0.0001;
            rx = (py - ry) * aTan + px;
            yo = -64;
            xo = -yo * aTan;
        }
        if(ra < PI){
            //Looking down
            ry = (((int)py>>6)<<6) + 64;
            rx = (py - ry) * aTan + px;
            yo = 64;
            xo = -yo * aTan;
        }
        if(ra == 0 || ra == PI){
            //Looking left or right
            rx = px;
            ry = py;
            dof = 8;
        }
        while(dof < 8){
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            mp = my * mapX + mx;
            if(mp < mapX * mapY && map[mp] == 1){
                //Hit wall
                dof = 8;
            } else {
                //Next line
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        glColor3f(0, 1, 0);
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();
        
        //Check vertical lines
        dof = 0;
        float nTan = -tan(ra);
        if(ra > P2 && ra < P3){
            //Looking left
            rx = (((int)px>>6)<<6) - 0.0001;
            ry = (px - rx) * nTan + py;
            xo = -64;
            yo = -xo * nTan;
        }
        if(ra < P2 || ra > P3){
            //Looking right
            rx = (((int)px>>6)<<6) + 64;
            ry = (px - rx) * nTan + py;
            xo = 64;
            yo = -xo * nTan;
        }
        if(ra == 0 || ra == PI){
            //Looking up or down
            rx = px;
            ry = py;
            dof = 8;
        }
        while(dof < 8){
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            mp = my * mapX + mx;
            if(mp < mapX * mapY && map[mp] == 1){
                //Hit wall
                dof = 8;
            } else {
                //Next line
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        glColor3f(1, 0, 0);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();
    }
}

void display(){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     drawMap2D();
     drawPlayer();
     drawRays2D();
     glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y){
    if(key == 'a'){
        pa -= 0.1;
        if(pa < 0){
            pa += 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }
    if(key == 'd'){
        pa += 0.1;
        if(pa > 2 * PI){
            pa -= 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;;
    }
    if(key == 'w'){
        px += pdx;
        py += pdy;
    }
    if(key == 's'){
        px -= pdx;
        py -= pdy;
    }
    glutPostRedisplay();
}
    
void init(){
     glClearColor(0.3, 0.3, 0.3, 0);
     gluOrtho2D(0, 1024, 512, 0);
     px = 300;
     py = 300;
     pdx = cos(pa) * 5;
     pdy = sin(pa) * 5;
}

int main(int argc, char** argv){ 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 512);
    glutCreateWindow("Raycasting");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutMainLoop();
}
