/*
 * Helper.cpp
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#include "Helper.h"
#include <GL/glut.h>
#include <cmath>
#include "Vector2.h"
#include <iostream>
using namespace std;

const double Helper::GRAVITATIONALCONSTANT = 1;

void Helper::drawCircle(double radius, int segments){
	Vector2<double> current(radius,0);
	double angle = 2*M_PI/segments;

	double x = std::cos(angle);
	double y = -std::sin(angle);


	glBegin(GL_POLYGON);
	glVertex2d(current.getX(),current.getY());

	for(int i =0; i< segments-1;i++){
		Vector2<double> ortho = current.orthogonal();
		Vector2<double> next = x*current + y*ortho;

		glVertex2d(next.getX(),next.getY());
		current = next;
	}

	glEnd();
}
