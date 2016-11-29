// essential headers/libraries
#include <math.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

// init callback
void myInit(void)
{
	// set up light
	GLfloat light_ambient[] = { 0.4f, 0.4f, 0.4f, 1 };
	GLfloat light_diffuse[] = { 0.6f, 0.6f, 0.6f, 1 };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1 };
	GLfloat light_position[] = { 1, 1, 3, 0 };
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
	glLineWidth(2.0);					// a line is 2 pixels wide

	glMatrixMode(GL_PROJECTION);							// set matrix mode
	glLoadIdentity();										// lead identity matrix
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);	// orthographic mapping

}

void drawStage()
{

	GLfloat x, y;

	GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1 };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1 };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1 };
	GLfloat mat_shininess = { 100.0f };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	for (x = -8.0f; x < 8.0f; x = x + 0.1) {
		for (y = -7.5f; y < 8.0f; y = y + 0.1) {
			glBegin(GL_POLYGON);
				glVertex3f(x, y, 0);
				glVertex3f(x + 0.1, y, 0);
				glVertex3f(x + 0.1, y + 0.1, 0);
				glVertex3f(x, y + 0.1, 0);
			glEnd();
		}
	}

}

void drawStage2(int w, int h)
{
	int i, j;

	float dw = 1.0 / w;
	float dh = 1.0 / h;

	GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1 };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1 };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1 };
	GLfloat mat_shininess = { 100.0f };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix(); // floor
		glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotate from vertical
		glScalef(50.0, 50.0, 50.0);
		glEnable(GL_POLYGON_OFFSET_FILL);
		for (j = 0; j < 100; ++j) {
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0; i <= 100; ++i) {
				glVertex2f(dw * i - 0.5, dh * (j + 1) - 0.5);
				glVertex2f(dw * i - 0.5, dh * j - 0.5);
			}
			glEnd();
		}
		glDisable(GL_POLYGON_OFFSET_FILL);
	glPopMatrix();
}

void drawSphere()
{
	GLUquadricObj*	sphereQuadric;
	sphereQuadric = gluNewQuadric();
	gluQuadricDrawStyle(sphereQuadric, GLU_FILL);

	GLfloat mat_ambient[] = { 0.3f, 0.0f, 0.0f, 1 };
	GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1 };
	GLfloat mat_specular[] = { 1.0f, 0.0f, 0.0f, 1 };
	GLfloat mat_shininess = { 100.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	glPushMatrix(); // red sphere
		glTranslatef(0, 0, 0);
		gluSphere(sphereQuadric, 2, 25, 25);
	glPopMatrix();
}

// display callback
void display(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear color and depth buffers

	glNormal3f(0, 0, 1);

	drawStage();
	drawStage2(100, 100);
	drawSphere();

	glutSwapBuffers();
}


// reshape callback
void reshape(int w, int h)
{

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