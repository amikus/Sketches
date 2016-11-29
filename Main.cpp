// essential headers/libraries
#include <math.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// init callback
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);	// background color: black
	glColor3f(0.0f, 0.0f, 0.0f);		// drawing color: white
	glLineWidth(2.0);					// a line is 2 pixels wide

	glMatrixMode(GL_PROJECTION);							// set matrix mode
	glLoadIdentity();										// lead identity matrix
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);	// orthographic mapping

	// set up ability to track object depths
	glClearDepth(1.0f);					// set clearing distance for depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

}

// display callback
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear color and depth buffers

	glutSwapBuffers();
}

// reshape callback
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-10.0f, 10.0f, -10.0f * (GLfloat)h / (GLfloat)w, 10.0f * (GLfloat)h / (GLfloat)w, -10.0f, 10.0f);
	}
	else {
		glOrtho(-10.0f * (GLfloat)w / (GLfloat)h, 10.0f * (GLfloat)w / (GLfloat)h, -10.0f, 10.0f, -10.0f, 10.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

int main(int argc, char** argv)
{
	// basic glut setup
	glutInit(&argc, argv);										// initialize toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// set display mode
	glutInitWindowSize(700, 700);								// set window size
	glutInitWindowPosition(100, 100);							// set window position on screen
	glutCreateWindow("Sketches");								// open screen window
	
	// register callback functions
	myInit();						// additional inits
	glutDisplayFunc(display);		// redraw to window
	glutReshapeFunc(reshape);		// reshape window

	glutMainLoop();

}