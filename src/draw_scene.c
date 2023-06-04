#include "draw_scene.h"
#include "3D_tools.h"
#include <math.h>

#define NUM_FACES 6
#define NUM_VERTICES 4
#define NUM_TURNS 20
#define FACE_SIZE 2.0f
#define SQUARE_SIZE 0.5f


void drawFrame()
{
    glBegin(GL_LINES);
        glColor3f(10.,0.,0.);
        glVertex3f(-10,0,0);
        glVertex3f(10,0,0);

        glColor3f(0.,10.,0.);
        glVertex3f(0, -10, 0);
        glVertex3f(0, 10, 0); 

        glColor3f(0.,0.,10.);
        glVertex3f(0, 0, -10);
        glVertex3f(0, 0, 10);

    glEnd(); 
}


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
    for(i=1; i<6; i++)
    {
        glPushMatrix();
		glTranslatef(-i*FACE_SIZE, 0., 0.); 
		drawTunnel(); 
    }
}


void drawCube() {
    // Face 1
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.1f);
    drawSquare();
    glPopMatrix();

    // Face 2
    glPushMatrix();
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.1f);
    drawSquare();
    glPopMatrix();

    // Face 3
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.1f);
    drawSquare();
    glPopMatrix();

    // Face 4
    glPushMatrix();
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.1f);
    drawSquare();
    glPopMatrix();

    // Face 5
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.1f);
    drawSquare();
    glPopMatrix();

    // Face 6
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.1f);
    drawSquare();
    glPopMatrix();
}

void drawRectangle() 
{
    glBegin(GL_QUADS);
        glVertex3f(-0.01f, -0.02f, 0.0f); // coin inférieur gauche
        glVertex3f(0.01f, -0.02f, 0.0f);  // coin inférieur droit
        glVertex3f(0.01f, 0.02f, 0.0f);   // coin supérieur droit
        glVertex3f(-0.01f, 0.02f, 0.0f);  // coin supérieur gauche
    glEnd();
}

void drawRaquette()
{
    glPushMatrix();

    // Face avant
    glScalef(0.02,0.1,0.); 
    drawRectangle();
    glTranslatef(0.0f, 0.0f, -0.1f);

    // Face arrière
    glScalef(0.02,0.1,0.);
    drawRectangle();
    glTranslatef(0.0f, 0.05f, 0.05f);

    // Côté droit
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.02,0.1,0.);
    drawRectangle();
    glTranslatef(0.0f, 0.0f, -0.02f);

    // Côté gauche
    glScalef(0.02,0.1,0.);
    drawRectangle();

    glPopMatrix();

}


void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(FACE_SIZE * 2.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
    gluLookAt(2.7f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
}

/*void drawCarre()
{
	glLoadIdentity();
        glTranslatef(squarePosX, squarePosY, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(-0.1f, -0.1f);
            glVertex2f(0.1f, -0.1f);
            glVertex2f(0.1f, 0.1f);
            glVertex2f(-0.1f, 0.1f);
        glEnd();
}*/

void drawBase()
{
    glPushMatrix();
        glScalef(3, 3, 10);
        glColor3f(235/255.,207/255.,52/255.);
        drawCone(); 
        glScalef(2,2,2);
        drawCircle();
    glPopMatrix();
}