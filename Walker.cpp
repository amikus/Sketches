#include "Walker.h"

// Walker constructor
Walker::Walker(int xPosition, int yPosition, int zPosition, float r, float g, float b) {

	// set pen coordinates
	this->xPosition = xPosition;
	this->yPosition = yPosition;
	this->zPosition = zPosition;

	this->red = r;
	this->green = g;
	this->blue = b;

};


// Walker destructor
Walker::~Walker() {

}

// update Walker's coordinates based on xPosition, yPosition, and zPosition
void Walker::updatePosition() {

	GLfloat randX = (rand() % 3 - 1) / 10.0f;
	GLfloat randY = (rand() % 3 - 1) / 10.0f;
	GLfloat randZ = (rand() % 3 - 1) / 10.0f;

	GLfloat tempX = xPosition + randX;
	GLfloat tempY = yPosition + randY;
	GLfloat tempZ = zPosition + randZ;

	if (tempX >= -50 && tempX <= 50 &&
		tempY >= -5 && tempY <= 5 &&
		tempZ >= -50 && tempZ <= 50)
		{
			xPosition = tempX;
			yPosition = tempY;
			zPosition = tempZ;

			drawDot(xPosition, yPosition, zPosition);
		}


	
}

void Walker::drawTinySphere(float x, float y, float z)
{

	GLfloat mat_ambient[] = { red * 0.3f, green * 0.3f, blue * 0.3f, 1 };
	GLfloat mat_diffuse[] = { red * 1.0f, green * 1.0f, blue * 1.0f, 1 };
	GLfloat mat_specular[] = { red * 1.0f, green * 1.0f, blue * 1.0f, 1 };
	GLfloat mat_shininess = { 100.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	GLUquadricObj*	sphereQuadric;
	sphereQuadric = gluNewQuadric();
	gluQuadricDrawStyle(sphereQuadric, GLU_FILL);

	glPushMatrix(); // red dot
	glTranslatef(x, y, z);
	gluSphere(sphereQuadric, .1, 5, 5);
	glPopMatrix();

}

// draw Walker and create dot array
void Walker::draw() {

	// draw dot array
	vector<Point>::const_iterator it;

	for (it = points.begin(); it != points.end(); ++it) {
		drawTinySphere((*it).x, (*it).y, (*it).z);
	}


}

// add dot coordinate to dot array
void Walker::drawDot(float xPosition, float yPosition, float zPosition) {
	points.push_back(Point(xPosition, yPosition, zPosition));
}
