#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "3D_tools.h"
#include "draw_scene.h"
#include "tunnel.h"
#include <time.h>
#include "stb_image.h"


#define NUM_FACES 6
#define NUM_VERTICES 4
#define NUM_TURNS 20
#define FACE_SIZE 2.0f



/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "Projet";
static float aspectRatio = 1.0;


/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;


/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,aspectRatio,Z_NEAR,Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}



int sphereMoving  = 0; // 0:immobile et 1:mouvement

//int menuActive = 1; /*1: actif, 0: inactif*/ 

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_SPACE:
                sphereMoving = 1; // Inverse l'état de déplacement de la sphère
                break;
        }
    }
}

	/* Variables pour stocker la position de la souris */
	double mouseX, mouseY;

/* Gestionnaire d'événements pour la souris */
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseX = xpos;
	mouseY = ypos;
}

float spherePosition = 0.0f;


float racketPosition = 0.0f;

void onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	//Gestion raquette
   
	 if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // Avancer la raquette sur l'axe z
        racketPosition -= 0.1f; // Mettez à jour la valeur selon la distance souhaitée
    }
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        // Avancer la raquette sur l'axe z
        racketPosition += 0.1f; // Mettez à jour la valeur selon la distance souhaitée
    }

	//gestion Menu 
	/*if (action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        if (menuActive) {
            // Vérifiez si le clic se situe dans la zone de l'option "Jouer"
            if (xpos >= 200 && xpos <= 400 && ypos >= 200 && ypos <= 250) {
                menuActive = 0; // Désactive le menu
                // Ajoutez ici votre code pour lancer le jeu
            }
            
            // Vérifiez si le clic se situe dans la zone de l'option "Quitter"
            if (xpos >= 200 && xpos <= 400 && ypos >= 300 && ypos <= 350) {
                glfwSetWindowShouldClose(window, GLFW_TRUE); // Ferme la fenêtre
            }
        }
    }*/
}





int main(int argc, char** argv)
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;



	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(5.0);

	glEnable(GL_DEPTH_TEST);

	/* Initialiser le gestionnaire d'événements pour la souris */
    glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetMouseButtonCallback(window, onMouseButton);

	glEnable(GL_LIGHTING);



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) 
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setupCamera();

		/*if (menuActive) {
            // Dessinez le menu
    
            // Écoutez les clics de souris
            glfwSetMouseButtonCallback(window, onMouseButton);
        }
        else {
            // Dessinez le jeu
            // ...
        }*/

		/* Scene rendering */
		//drawFrame();

		glPushMatrix();
		drawLongTunnel(); 
		glPopMatrix(); 


		// Dessin de la raquette 

		/* Mettre à jour les transformations de la raquette*/

		
		glPushMatrix();
		glColor3f(0.,1.,0.);
		glRotatef(90., 0.,1.,0.);
		glTranslatef(0., 0., 2.6); 
		glScalef(0.09,0.09,0.09);
		glTranslatef((mouseX - WINDOW_WIDTH/2) * 0.001, -(mouseY - WINDOW_HEIGHT/2) * 0.001, racketPosition); // déplacer horizontalement et verticalement en fonction de la position de la souris
		drawSquare();
		glPopMatrix();
		

		//Gestion sphère 

		//Mouvement sphere quand clique droit 
		if (sphereMoving)
		{
			// Mettre à jour la position de la sphère
			spherePosition -= 0.01f; // Mettez à jour la valeur selon la vitesse souhaitée
			glEnable(GL_LIGHT1);
		}
        else
        {
            glDisable(GL_LIGHT1);
        }

		// Dessiner la sphère à la nouvelle position
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glRotatef(90., 0., 1., 0.);
		glTranslatef(0., 0., 2.6 + spherePosition);
		glScalef(0.01, 0.01, 0.01);
		drawSphere();
		glPopMatrix();


	
		//Positionnement aléatoire des obstacles 
		//obstacle(); 



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}

		/* Animate scenery */
	}

	glfwTerminate();
	return 0;
}