#pragma once

// required include statements
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

class Walker {

private:

	// variables that define walker's appearance
	const int walkerSize = 2;
	const int halfWalkerSize = 1;

	// changeable variables
	void drawTinySphere(float, float, float);

	// used for storing dot coordinates
	struct Point {
		float x, y, z;
		Point(float px, float py, float pz) : x(px), y(py), z(pz) {}
	};

public:
	// array of dot coordinates
	vector<Point> points;

	float xPosition, yPosition,
		  zPosition;				// pen coordinates

	float red, green, blue;			// color values

	void updatePosition();			// update walker's corner coordinates
	void draw();					// draw ball and dot array
	void drawDot(float, float, float);		// add dot coordinate to dot array

	Walker(int, int, int, float, float, float);			// Walker constructor
	~Walker();						// Walker destructor


};