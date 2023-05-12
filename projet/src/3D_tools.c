#include "3D_tools.h"

/* Camera parameters and functions */
float theta = 45.0f; // Angle between x axis and viewpoint
float phy = 60.0f; // Angle between z axis and viewpoint
float dist_zoom = 30.0f; // Distance between origin and viewpoint

void setCamera() {
	gluLookAt(10. , 0., 0.,
			//dist_zoom*cos(toRad(theta))*sin(toRad(phy)),
			//  dist_zoom*sin(toRad(theta))*sin(toRad(phy)),
			//  dist_zoom*cos(toRad(phy)), //coordonnées de la caméra
			  0.0,0.0,0.0, //coordonnées de ce que l'on regarde (ici origine)
			  0.0,0.0,1.0); // direction du haut

			// x positif vers moi, z vers le haut, y vers la droite 
}

/* Convert degree to radians */
float toRad(float deg) {
	return deg*M_PI/180.0f;
}


void drawPS() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.5,-0.5,0.0);
		glVertex3f(0.5,0.5,0.0);
		glVertex3f(-0.5,0.5,0.0);
	glEnd();
}

void drawMur() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-0.5,0.0,-5.0);
		glVertex3f(0.5,0.0,-0.5);
		glVertex3f(0.5,0.0,0.5);
		glVertex3f(-0.5,0.,0.5);
	glEnd();
}


void drawCircle() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,0.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawCone() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,1.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawSphere() {

	glColor3f(0.5,0.5,0.8);
	glScalef(0.6,0.6,0.6);
	gluSphere(gluNewQuadric(),1.0,NB_SEG_CIRCLE,NB_SEG_CIRCLE);

}
