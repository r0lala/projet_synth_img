#include "draw_scene.h"
#include "3D_tools.h"
#include <math.h>
       
        
void drawCorridor() { 

    //Sol
        glPushMatrix();
            glTranslatef(0.0,0.0,-8.0);
            glScalef(100.0,30.0,1.);
            glColor3f(0.3,0.0,0.5);
            drawPS();
		glPopMatrix();

  //Plafond
          glPushMatrix();
              glTranslatef(0.0,0.0,8.);
              glScalef(100.0,30.0,1.);
              glColor3f(0.3,0.,0.5);
              drawPS();
      glPopMatrix();

    //MurDroit
		glPushMatrix();
            glTranslatef(0.0,8.0,0.0);
            glScalef(100.0,1.0,30.);
            glColor3f(0.3,0.2,0.5);
            drawMur();
		glPopMatrix();

    //MurGauche
		glPushMatrix();
            glTranslatef(0.0,-8.0,0.0);
            glScalef(100.0,10.0,30.);
            glColor3f(0.3,0.2,0.5);
            drawMur();
		glPopMatrix();
}