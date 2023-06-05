#include "obstacles.h"
#include "3D_tools.h"
#include "draw_scene.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FACES 6
#define NUM_VERTICES 4
#define NUM_TURNS 20
#define FACE_SIZE 2.0f
#define SQUARE_SIZE 0.5f

static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;



void obstacle1() {

    glPushMatrix();
	glColor3f(0.2,0.3,0.3);
    glTranslatef(-1.5,-0.6,0.7); 
	glScalef(0.3,0.3,0.3);
    //glRotatef(90., 0., 1., 0.);
	glBegin(GL_QUADS);
		glVertex3f(-4.0, -3.0, -2.0);
		glVertex3f(-4.0, 1.0, -2.0);
		glVertex3f(-4.0, 1.0, 1.0);
		glVertex3f(-4.0, -3.0, 1.0);
	glEnd();
    glPopMatrix();
}

void obstacle2() {

    glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(1.6,-0.1,-0.6); 
	glScalef(0.3,0.3,0.3);
	glBegin(GL_QUADS);
		glVertex3f(-6.0, -3.0, -1.0);
		glVertex3f(-6.0, 1.0, -1.0);
		glVertex3f(-6.0, 1.0, 1.0);
		glVertex3f(-6.0, -3.0, 1.0);
	glEnd();
    glPopMatrix();
}

void obstacle3() {

    glPushMatrix(); 
	glColor3f(1.0f, 0.0f, 1.0f);
    glTranslatef(-1.,-0.1,-0.6); 
	glScalef(0.3,0.3,0.3);
	glBegin(GL_QUADS);
		glVertex3f(-6.0, -3.0, -1.0);
		glVertex3f(-6.0, 1.0, -1.0);
		glVertex3f(-6.0, 1.0, 1.0);
		glVertex3f(-6.0, -3.0, 1.0);
	glEnd();
    glPopMatrix();
}

void obstacle4() {

    glPushMatrix(); 
	glColor3f(0.0f, 1.0f, 1.0f);
    glTranslatef(-4.,-0.1,0.6); 
	glScalef(0.3,0.3,0.3);
	glBegin(GL_QUADS);
		glVertex3f(-6.0, -3.0, -1.0);
		glVertex3f(-6.0, 1.0, -1.0);
		glVertex3f(-6.0, 1.0, 1.0);
		glVertex3f(-6.0, -3.0, 1.0);
	glEnd();
    glPopMatrix(); 
}



