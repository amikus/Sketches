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
	drawBall();
};


// Walker destructor
Walker::~Walker() {

}

// update Walker's coordinates based on xPosition, yPosition, and zPosition
void Walker::updatePosition() {

	// bottom left corner
	// draw the ball here
}

// draw Walker and create dot array
void Walker::drawBall() {

	// draw dot array
	vector<Point>::const_iterator it;
	for (it = points.begin(); it != points.end(); ++it) {
		glBegin(GL_POINTS);
		glVertex2i((*it).x, (*it).y);
		glEnd();
	}

	// set color to green
	glColor3f(0.0f, 1.0f, 0.0f);

	// draw Ball

	// set color back to white
	glColor3f(1.0f, 1.0f, 1.0f);

}

// add dot coordinate to dot array
void Walker::drawDot(float xPosition, float yPosition) {
	points.push_back(Point(xPosition, yPosition));
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