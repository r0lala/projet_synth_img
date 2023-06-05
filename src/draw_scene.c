#include "draw_scene.h"
#include "3D_tools.h"
#include <math.h>
#include <stdlib.h>

#define NUM_FACES 6
#define NUM_VERTICES 4
#define NUM_TURNS 20
#define FACE_SIZE 2.0f
#define SQUARE_SIZE 0.5f

static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;



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

/* Light properties */
GLfloat sphere_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat sphere_light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat sphere_light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat sphere_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat light_position[] = { 2.7f, 0.0f, 0.0f, 1.0f };   // Position de la source de lumière
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };    // Composante ambiante de la lumière
GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };    // Composante diffuse de la lumière
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // Composante spéculaire de la lumière

void setupCamera() 
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);      // Positionne la lumière
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);        // Définit la composante ambiante
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);        // Définit la composante diffuse
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);      // Définit la composante spéculaire
    glEnable(GL_LIGHT0);  
    glLightfv(GL_LIGHT1, GL_POSITION, sphere_light_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, sphere_light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, sphere_light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, sphere_light_specular);
    gluLookAt(2.7f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
}



   

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