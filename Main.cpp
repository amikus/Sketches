// essential headers/libraries
#include <math.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Walker.h"

using namespace std;

GLuint WIN_WIDTH, WIN_HEIGHT;
GLfloat eyeX = 0.0f, eyeY = 0.0f, eyeZ = 0.0f;	// starting eye position
GLfloat lightSourceX = -3.0f, lightSourceY = 10.0f, lightSourceZ = 5.0f; // location of light source
GLfloat light_position[] = { lightSourceX,	lightSourceY,	lightSourceZ,	.5f }; // light 0 position

//Create Walkers
Walker redWalker(0, 0, 0, 1, 0, 0);
Walker greenWalker(0, 0, 0, 0, 1, 0);
Walker blueWalker(0, 0, 0, 0, 0, 1);
Walker yellowWalker(0, 0, 0, 1, 1, 0);
Walker tealWalker(0, 0, 0, 0, 1, 1);
Walker purpleWalker(0, 0, 0, 1, 0, 1);

// Submenus
GLuint toggleWalkers;
GLuint clearWalkers;

// Toggle spinning
GLuint spinToggle = 0;

// Toggle Walkers
GLuint redWalkerOn = 0;
GLuint greenWalkerOn = 0;
GLuint blueWalkerOn = 0;
GLuint yellowWalkerOn = 0;
GLuint tealWalkerOn = 0;
GLuint purpleWalkerOn = 0;

// init callback
void myInit(void)
{
	// set window size
	WIN_WIDTH = glutGet(GLUT_SCREEN_WIDTH) / 2.0;
	WIN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT) / 2.0;

	//set up light
	GLfloat light_ambient[] = { 0.9f, 0.9f, 0.9f, 1 };
	GLfloat light_diffuse[] = { 0.9f, 0.9f, 0.9f, 1 };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);

	// enable light
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);	// interpolate adjacent polygons shading
	glEnable(GL_NORMALIZE);		// set normal vectors to unit length

	// set up ability to track object depths
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0, 0.0, 0.0, 1.0);	// background color: black
	glColor3f(1.0f, 1.0f, 1.0f);		// drawing color: white

	glMatrixMode(GL_PROJECTION);							// set matrix mode
	glLoadIdentity();										// lead identity matrix

}

void drawStage(int w, int h)
{
	int i, j;

	float dw = 1.0f / w;
	float dh = 1.0f / h;

	GLfloat mat_ambient[] = { 0.3f, 0.32f, 0.3f, 1 };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1 };
	GLfloat mat_specular[] = { 0.7f, 0.7f, 0.7f, 1 };
	GLfloat mat_shininess = { 100.0f };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix(); // floor
		glTranslatef(0.0f, -6.0f, 0.0f);
		glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotate from vertical
		glScalef(40.0, 40.0, 40.0);
		glEnable(GL_POLYGON_OFFSET_FILL);
		for (j = 0; j < h; ++j) {
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0; i <= w; ++i) {
				glVertex2f(dw * i - 0.5f, dh * (j + 1) - 0.5f);
				glVertex2f(dw * i - 0.5f, dh * j - 0.5f);
			}
			glEnd();
		}
		glDisable(GL_POLYGON_OFFSET_FILL);
	glPopMatrix();
}

void myTimer(int iUnused)
{
	// update animations and redraw
	if (redWalkerOn) redWalker.updatePosition();
	if (greenWalkerOn) greenWalker.updatePosition();
	if (blueWalkerOn) blueWalker.updatePosition();
	if (yellowWalkerOn) yellowWalker.updatePosition();
	if (tealWalkerOn) tealWalker.updatePosition();
	if (purpleWalkerOn) purpleWalker.updatePosition();

	glutPostRedisplay();
}

// display callback
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glNormal3f(0, 0, 1);

	drawStage(100, 100);

	redWalker.draw();
	greenWalker.draw();
	blueWalker.draw();
	yellowWalker.draw();
	tealWalker.draw();
	purpleWalker.draw();

	glutSwapBuffers();

	// call timer to update animations and screen again
	glutTimerFunc(100, myTimer, 0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	WIN_WIDTH = w;
	WIN_HEIGHT = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		45.0f,
		(GLfloat)(WIN_WIDTH) / (GLfloat)(WIN_HEIGHT),
		0.1,
		70.0);
}

void mouse( int x, int y)
{

	// 3 * 360 degree possible
	double deg1 = (360.0 / WIN_WIDTH)*(double)x*3.0;
	// top and bottom views
	double deg2 = (180.0 / WIN_HEIGHT)*(double)y;
	double r = 30.0;
	if (deg1 > 360)deg1 = fmod(deg1, 360.0);
	eyeZ = r * sin(deg2*0.0174532) * cos(deg1*0.0174532);
	eyeX = r * sin(deg2*0.0174532) * sin(deg1*0.0174532);
	eyeY = r * cos(deg2*0.0174532);
	glutPostRedisplay();

}

void toggleWalkersMenu(int id)
{
	switch (id)
	{
	case 1:
		redWalkerOn ? redWalkerOn = 0 : redWalkerOn = 1;
		break;
	case 2:
		greenWalkerOn ? greenWalkerOn = 0 : greenWalkerOn = 1;
		break;
	case 3:
		blueWalkerOn ? blueWalkerOn = 0 : blueWalkerOn = 1;
		break;
	case 4:
		yellowWalkerOn ? yellowWalkerOn = 0 : yellowWalkerOn = 1;
		break;
	case 5:
		tealWalkerOn ? tealWalkerOn = 0 : tealWalkerOn = 1;
		break;
	case 6:
		purpleWalkerOn ? purpleWalkerOn = 0 : purpleWalkerOn = 1;
		break;
	case 7:
		redWalkerOn = 0;
		greenWalkerOn = 0;
		blueWalkerOn = 0;
		yellowWalkerOn = 0;
		tealWalkerOn = 0;
		purpleWalkerOn = 0;
		break;
	case 8:
		redWalkerOn = 1;
		greenWalkerOn = 1;
		blueWalkerOn = 1;
		yellowWalkerOn = 1;
		tealWalkerOn = 1;
		purpleWalkerOn = 1;
		break;

	}

}

void clearWalkersMenu(int id)
{
	switch (id)
	{
	case 1:
		redWalker.points = {};
		redWalker.xPosition = 0;
		redWalker.yPosition = 0;
		redWalker.zPosition = 0;
		break;
	case 2:
		greenWalker.points = {};
		greenWalker.xPosition = 0;
		greenWalker.yPosition = 0;
		greenWalker.zPosition = 0;
		break;
	case 3:
		blueWalker.points = {};
		blueWalker.xPosition = 0;
		blueWalker.yPosition = 0;
		blueWalker.zPosition = 0;
		break;
	case 4:
		yellowWalker.points = {};
		yellowWalker.xPosition = 0;
		yellowWalker.yPosition = 0;
		yellowWalker.zPosition = 0;
		break;
	case 5:
		tealWalker.points = {};
		tealWalker.xPosition = 0;
		tealWalker.yPosition = 0;
		tealWalker.zPosition = 0;
		break;
	case 6:
		purpleWalker.points = {};
		purpleWalker.xPosition = 0;
		purpleWalker.yPosition = 0;
		purpleWalker.zPosition = 0;
		break;
	case 7:
		redWalker.points = {};
		greenWalker.points = {};
		blueWalker.points = {};
		yellowWalker.points = {};
		tealWalker.points = {};
		purpleWalker.points = {};

		redWalker.xPosition = 0;
		redWalker.yPosition = 0;
		redWalker.zPosition = 0;
		greenWalker.xPosition = 0;
		greenWalker.yPosition = 0;
		greenWalker.zPosition = 0;
		blueWalker.xPosition = 0;
		blueWalker.yPosition = 0;
		blueWalker.zPosition = 0;
		yellowWalker.xPosition = 0;
		yellowWalker.yPosition = 0;
		yellowWalker.zPosition = 0;
		tealWalker.xPosition = 0;
		tealWalker.yPosition = 0;
		tealWalker.zPosition = 0;
		purpleWalker.xPosition = 0;
		purpleWalker.yPosition = 0;
		purpleWalker.zPosition = 0;
	}
}
void mainMenu(int id)
{

}

int main(int argc, char** argv)
{
	// basic glut setup
	glutInit(&argc, argv);	// initialize toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// set display mode
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);					// set window size
	glutInitWindowPosition(100, 100);							// set window position on screen
	glutCreateWindow("Sketches");								// open screen window
	
	// register callback functions
	myInit();									// additional inits
	glutDisplayFunc(display);					// redraw to window
	glutReshapeFunc(reshape);					// reshape window
	glutMotionFunc(mouse);						// govern active mouse actions

	// create menu system
	toggleWalkers = glutCreateMenu(toggleWalkersMenu);
		glutAddMenuEntry("red", 1);
		glutAddMenuEntry("green", 2);
		glutAddMenuEntry("blue", 3);
		glutAddMenuEntry("yellow", 4);
		glutAddMenuEntry("teal", 5);
		glutAddMenuEntry("purple", 6);
		glutAddMenuEntry("all off", 7);
		glutAddMenuEntry("all on", 8);
	clearWalkers = glutCreateMenu(clearWalkersMenu);
		glutAddMenuEntry("red", 1);
		glutAddMenuEntry("green", 2);
		glutAddMenuEntry("blue", 3);
		glutAddMenuEntry("yellow", 4);
		glutAddMenuEntry("teal", 5);
		glutAddMenuEntry("purple", 6);
		glutAddMenuEntry("all", 7);
	glutCreateMenu(mainMenu);
		glutAddSubMenu("Toggle walker activity", toggleWalkers);
		glutAddSubMenu("Clear walkers", clearWalkers);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

}