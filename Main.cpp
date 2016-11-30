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

GLuint WIN_WIDTH, WIN_HEIGHT;
GLfloat eyeX = 0.0f, eyeY = 0.0f, eyeZ = 0.0f;	// starting eye position
GLfloat lightSourceX = -3.0f, lightSourceY = 10.0f, lightSourceZ = 5.0f; // location of light source
GLfloat light_position[] = { lightSourceX,	lightSourceY,	lightSourceZ,	.5f }; // light 0 position

GLUquadricObj*	sphereQuadric;

// init callback
void myInit(void)
{
	// set window size
	WIN_WIDTH = glutGet(GLUT_SCREEN_WIDTH) / 2.0;
	WIN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT) / 2.0;

	//set up light
	GLfloat light_ambient[] = { 0.6f, 0.6f, 0.6f, 1 };
	GLfloat light_diffuse[] = { 0.6f, 0.6f, 0.6f, 1 };
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

	sphereQuadric = gluNewQuadric();
	gluQuadricDrawStyle(sphereQuadric, GLU_FILL);
	glPolygonOffset(1.0, 1.0);	// offset to distinguish shadow from floor

	// set up ability to track object depths
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0, 0.0, 0.0, 1.0);	// background color: black
	glColor3f(1.0f, 1.0f, 1.0f);		// drawing color: white
	glLineWidth(2.0);					// a line is 2 pixels wide

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
		glTranslatef(0.0f, -5.0f, 0.0f);
		glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotate from vertical
		glScalef(50.0, 50.0, 50.0);
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

void drawSphere()
{

	GLfloat mat_ambient[] = { 0.3f, 0.0f, 0.0f, 1 };
	GLfloat mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1 };
	GLfloat mat_specular[] = { 1.0f, 0.0f, 0.0f, 1 };
	GLfloat mat_shininess = { 100.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	glPushMatrix(); // red sphere
		glTranslatef(0.0f, 4.0f, 0.0f);
		gluSphere(sphereQuadric, 1, 25, 25);
	glPopMatrix();
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
	drawSphere();

	glutSwapBuffers();
}

void reshape(int w, int h) {
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

void mouseMovement(int x, int y) {
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

int main(int argc, char** argv)
{
	// basic glut setup
	glutInit(&argc, argv);	// initialize toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// set display mode
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);					// set window size
	glutInitWindowPosition(100, 100);							// set window position on screen
	glutCreateWindow("Sketches");								// open screen window
	
	// register callback functions
	myInit();						// additional inits
	glutDisplayFunc(display);		// redraw to window
	glutReshapeFunc(reshape);		// reshape window
	glutPassiveMotionFunc(mouseMovement);

	glutMainLoop();

}