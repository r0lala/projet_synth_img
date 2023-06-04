#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "3D_tools.h"
#include "draw_scene.h"
#include<time.h>

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


void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			case GLFW_KEY_R :
				flag_animate_rot_arm = 1-flag_animate_rot_arm;
				break;
			case GLFW_KEY_T :
				flag_animate_rot_scale = 1-flag_animate_rot_scale;
				break;
			case GLFW_KEY_KP_9 :
				if(dist_zoom<100.0f) dist_zoom*=1.1;
				printf("Zoom is %f\n",dist_zoom);
				break;
			case GLFW_KEY_KP_3 :
				if(dist_zoom>1.0f) dist_zoom*=0.9;
				printf("Zoom is %f\n",dist_zoom);
				break;
			case GLFW_KEY_UP :
				if (phy>2) phy -= 2;
				printf("Phy %f\n",phy);
				break;
			case GLFW_KEY_DOWN :
				if (phy<=88.) phy += 2;
				printf("Phy %f\n",phy);
				break;
			case GLFW_KEY_LEFT :
				theta -= 5;
				break;
			case GLFW_KEY_RIGHT :
				theta += 5;
				break;
			default: fprintf(stdout,"Touche non gérée (%d)\n",key);
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


	float pos_x = -6.0;
	float pos_y = 0; 
	float pos_z = 0;  
	float square_pos_x =0; 
	float square_pos_y = 0;
	float square_pos_z =2.6;  
	float square_size = 0.1; 
	float radius = 1.0; 

//test Collision entre la raquette et la sphère 
/*void Collision() 
{
    // Efface le buffer de couleur et le buffer de profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Définit la position de la caméra
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setCamera();

    // Dessine le carré
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    drawSquare();
    glPopMatrix();

    // Dessine la sphère
	static float speed = 0.0f;
        speed += 0.04f;
		glTranslatef(speed, 0., 0.);

	glColor3f(1.0f, 0.0f, 0.0f); 
    glPushMatrix();
    glTranslatef(pos_x, pos_y, pos_z);
	glScalef(0.2,0.2,0.2);
    drawSphere();
    glPopMatrix();


    // Gestion de la collision avec le carré
    if (pos_x + radius > square_pos_x - square_size && pos_x - radius < square_pos_x + square_size &&
        pos_y + radius > square_pos_y - square_size && pos_y - radius < square_pos_y + square_size)
    {
        speed = -speed; // Inverse la direction de la sphère en x
    }

    // Déplace la sphère
    pos_x += speed;
    pos_y += speed;

    // Échange la mémoire du front et du back buffer
    glFinish();
}*/



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

		/* Scene rendering */
		//drawFrame();

		glPushMatrix();
		drawLongTunnel(); 
		glPopMatrix(); 

		// Dessin de la raquette 
		/* Mettre à jour les transformations */
		glPushMatrix();
		glColor3f(0.,1.,0.);
		glRotatef(90., 0.,1.,0.);
		glTranslatef(0., 0., 2.6);
		glScalef(0.09,0.09,0.09);
		glTranslatef((mouseX - WINDOW_WIDTH/2) * 0.001, -(mouseY - WINDOW_HEIGHT/2) * 0.001, 0.); // déplacer horizontalement en fonction de la position de la souris
		drawSquare();
		glPopMatrix();
		
		//Positionnement de la sphère
		static float x = 0.0f;
        x += 0.04f;
		glTranslatef(x, 0., 0.);

		//Dessin de la sphère 

		glColor3f(1.0f, 0.0f, 0.0f); 
        glPushMatrix();
        glTranslatef(-6.0f, 0.0f, 0.0f); // positionner la sphère au centre du tunnel
		glScalef(0.2,0.2,0.2);
        drawSphere();
        glPopMatrix();

		//Collision(); 

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