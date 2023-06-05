#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "3D_tools.h"
#include "draw_scene.h"
#include "menu.h"
#include "obstacles.h"
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

void drawImage(const char* imagePath)
{
    int width, height, channels;
    unsigned char* image = stbi_load(imagePath, &width, &height, &channels, STBI_rgb_alpha);
    if (image)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1); // Utilisez les dimensions de la fenêtre

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glEnable(GL_TEXTURE_2D);
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(WINDOW_WIDTH, 0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(0.0, WINDOW_HEIGHT);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        stbi_image_free(image);
    }
    else
    {
        fprintf(stderr, "Failed to load image: %s\n", imagePath);
    }
}

int sphereMoving  = 0; // 0:immobile et 1:mouvement
int showMenu = 1; // 1: afficher le menu, 0: afficher le reste du jeu


float sphereDirection[3] = {0.0f, 0.0f, 0.0f};
int spherePositionx = 0; 
int spherePositiony = 0;  

float dirX, dirY, dirZ, length;

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) 
	{
		
        switch(key) 
		{
            case GLFW_KEY_SPACE:
                sphereMoving = 1; // Inverse l'état de déplacement de la sphère
                break;
			case GLFW_KEY_J:
                    if (showMenu)
                    {
                        showMenu = 0; // Afficher le reste du jeu
                    }
                    break;
			case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, GLFW_TRUE); // Fermer la fenêtre
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

	int bloc = (rand()%4)+1; 

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


		if (showMenu)
		{
			// Afficher le menu
			drawImage("./doc/menu_LightCorridor.png");
			 
		}
		else
		{
		
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

		//Mouvement sphere quand clique sur espace
		if (sphereMoving)
		{

			// Générer des valeurs aléatoires pour les composantes x, y et z du vecteur de direction
				dirX = (float)(rand() % 100 - 50) / 100.0f; // Valeur aléatoire entre -0.5 et 0.5
				dirY = (float)(rand() % 100 - 50) / 100.0f; // Valeur aléatoire entre -0.5 et 0.5
				dirZ = (float)(rand() % 100 - 50) / 100.0f; // Valeur aléatoire entre -0.5 et 0.5

				// Normaliser le vecteur de direction pour avoir une longueur de 1
				length = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
				dirX /= length;
				dirY /= length;
				dirZ /= length;

				// Appliquer le vecteur de direction à la sphère

				sphereDirection[0] = dirX;
				sphereDirection[1] = dirY;
				sphereDirection[2] = dirZ;

			spherePositionx += dirX * 0.000007;
			spherePositiony += dirY * 0.000007;
			spherePosition -= dirZ * 0.000007f; // Mettez à jour la valeur selon la vitesse souhaitée
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
		glTranslatef(spherePositionx*sphereDirection[0], spherePositiony*sphereDirection[1], 2.6 + spherePosition*sphereDirection[2]);
		glScalef(0.007, 0.007, 0.007);
		drawSphere();
		glPopMatrix();

		//Positionnement aléatoire des obstacles 

			if(bloc==1)
			{
				obstacle1();
			}
			else if(bloc==2)
			{
				obstacle2();
			}
			else if(bloc==3)
			{
				obstacle3();
			}
			else if(bloc==4)
			{
				obstacle4();
			}
		}
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