#include "Walker.h"

// Walker constructor
Walker::Walker(int xPosition, int yPosition, int zPosition) {

	// set pen coordinates
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	this->zPosition = zPosition;

	// set Walker's coordinates based
	// on coordinates specified above
	updatePosition();

	// draw the ball
	draw();
};


// Walker destructor
Walker::~Walker() {

}

// update Walker's coordinates based on xPosition, yPosition, and zPosition
void Walker::updatePosition() {

	// bottom left corner
	// draw the ball here
}

void Walker::drawSphere()
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
	glTranslatef(0.0f, 4.0f, 0.0f);
	gluSphere(sphereQuadric, 1, 25, 25);
	glPopMatrix();
}

// draw Walker and create dot array
void Walker::draw() {

	// draw dot array
	vector<Point>::const_iterator it;

	for (it = points.begin(); it != points.end(); ++it) {
		glBegin(GL_POINTS);
			glVertex3f((*it).x, (*it).y, (*it).z);
		glEnd();
	}

	// set pen color to red
	glColor3f(1.0f, 0.0f, 0.0f);

	// draw Ball
	drawSphere();

	// set color back to white
	glColor3f(1.0f, 1.0f, 1.0f);

}

// add dot coordinate to dot array
void Walker::drawDot(float xPosition, float yPosition, float zPosition) {
	points.push_back(Point(xPosition, yPosition, zPosition));
}

// update penPosition
void Walker::toggleDrawing(string drawing) {

	if (drawing == "up") {
		this->drawing = 0;
	}
	else if (drawing == "down") {
		this->drawing = 1;
	}
}