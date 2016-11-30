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
	const int walkerSize = 30;
	const int halfWalkerSize = 15;

	// changeable variables


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
	bool drawing;					// turns drawing on and off

	void toggleDrawing(string);		// update pen position
	void updatePosition();			// update walker's corner coordinates
	void draw();					// draw ball and dot array
	void drawDot(float, float, float);		// add dot coordinate to dot array

	Walker(int, int, int);			// Walker constructor
	~Walker();						// Walker destructor


};