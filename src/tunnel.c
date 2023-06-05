#include "draw_scene.h"
#include "3D_tools.h"
#include <math.h>

#define NUM_FACES 6
#define NUM_VERTICES 4
#define NUM_TURNS 20
#define FACE_SIZE 2.0f
#define SQUARE_SIZE 0.5f


//Dessine une portion de Tunnel
void drawTunnel() {

    glPushMatrix();
    glTranslatef(-FACE_SIZE / 2.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);

    for (int i = 0; i < NUM_TURNS; i++) {
        float x1 = i * FACE_SIZE / NUM_TURNS;
        float x2 = (i + 1) * FACE_SIZE / NUM_TURNS;
        float y1 = -FACE_SIZE / 2.0f;
        float y2 = FACE_SIZE / 2.0f;
        float z1 = -FACE_SIZE / 2.0f;
        float z2 = FACE_SIZE / 2.0f;

        for (int j = 0; j < NUM_FACES; j++) {
            switch (j) {
                case 0:
                    glColor3f(0.0f, 0.0f, 0.8f); // Rouge
                    glVertex3f(x2, y2, z1);
                    glVertex3f(x2, y1, z1);
                    glVertex3f(x1, y1, z1);
                    glVertex3f(x1, y2, z1);
                    break;
                case 1:
                    glColor3f(0.0f, 0.0f, 0.8f); // Vert
                    glVertex3f(x1, y2, z2);
                    glVertex3f(x1, y1, z2);
                    glVertex3f(x2, y1, z2);
                    glVertex3f(x2, y2, z2);
                    break;
                case 2:
                    glColor3f(0.0f, 0.0f, 1.0f); // Magenta
                    glVertex3f(x2, y1, z1);
                    glVertex3f(x2, y1, z2);
                    glVertex3f(x1, y1, z2);
                    glVertex3f(x1, y1, z1);
                    break;
                case 3:
                    glColor3f(0.0f, 0.0f, 1.0f); // Cyan
                    glVertex3f(x1, y2, z1);
                    glVertex3f(x1, y2, z2);
                    glVertex3f(x2, y2, z2);
                    glVertex3f(x2, y2, z1);
                    break;
            }
        }
    }

    glEnd();
    glPopMatrix();
}


//Dessine la totalité du Tunnel 
void drawLongTunnel()
{
    drawTunnel();
    int i; 
    for(i=1; i<7; i++)
    {
        glPushMatrix();
		glTranslatef(-i*FACE_SIZE, 0., 0.); 
		drawTunnel(); 
    }
}