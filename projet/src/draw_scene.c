#include "draw_scene.h"
#include "3D_tools.h"
#include <math.h>


void drawBase() {
    //base ronde
    glPushMatrix();
        glColor3f(235.0/255.0, 207.0/255.0, 52.0/255.0);
        glScalef(3.0,3.0,0.);
        drawCircle();
    glPopMatrix();

    //cone
    glPushMatrix();
        glScalef(2.0,2.0,10.);
        drawCone();
    glPopMatrix();

}

void drawFrame(){
    glBegin(GL_LINES);
    glColor3f(0.6,0.8,0.6);
        glVertex3f(0.0,0.0,0.0); // 3f por 3 coordonnées
        glVertex3f(10.0,0.0,0.0);
        glVertex3f(0.0,0.0,0.0); 
        glVertex3f(0.0,10.0,0.0);
        glVertex3f(0.0,0.0,0.0); 
        glVertex3f(0.0,0.0,10.0);
    glEnd();
}

// TD2 exo3
//void drawCircle(){
//     int segments =30;
//     glBegin(GL_LINE_LOOP);
//         for(int i=0; i<segments ; i++){
//             int aplha = ((i*2*pi)/segments);
//             glVertex2f(sin(alpha), cos(alpha));
//         }
//     glEnd();
// }

void drawArm() {
    //sphère
    glPushMatrix();
        glColor3f(245.0/255.0, 164.0/255.0, 66.0/255.0);
        glTranslatef(0.,0.,10.);
        glScalef(3.2/2., 3.2/2., 3.2/2.);
        drawSphere();
    glPopMatrix();

    //cone
    glPushMatrix();
        glTranslatef(0.0,0.0,10.0);
        glRotatef(90, 0., 1., 0.);
        glScalef(1.0, 1.0, 10.0);
        drawCone();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0,0.0,10.0);
        glRotatef(-90, 0., 1., 0.);
        glScalef(1.0, 1.0, 10.0);
        drawCone();
    glPopMatrix();
}

void drawPan() {
    // Plateau 1
    glPushMatrix();
        glColor3f(89.0/255.0, 115.0/255.0, 200.0/255.0);
        glTranslatef(10.0, 0.0, 5.0);
        glScalef(3.0, 3.0, 3.0);
        drawCircle();
    glPopMatrix();

    glPushMatrix();
        int segments =3;
        glColor3f(200.0/255.0, 15.0/255.0, 100.0/255.0);
        glTranslatef(10.0, 0.0, 10.0);
        glBegin(GL_LINES);
        for(int i=0; i<segments ; i++){
            int alpha = ((i*2*M_PI)/segments);
            glVertex3f(0,0,0);
            glVertex3f(sin(alpha)*3, cos(alpha)*3,-5.);
        } 
        glEnd();

    glPopMatrix();

}
