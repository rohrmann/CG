/*
 * Triangle.cpp
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#include "Triangle.h"
#include <GL/glut.h>

Triangle::Triangle(Vector2<double> a,Vector2<double> b, Vector2<double> c, Vector4<double> color,double angle, double rotationSpeed):a(a),b(b),c(c),color(color){
	this->rotationSpeed = rotationSpeed;
	this->angle = angle;
}

void Triangle::draw(){
	glPushMatrix();
	glRotated(angle,0,0,1);

	glBegin(GL_POLYGON);
	glColor4d(color.getX(),color.getY(),color.getZ(),color.getA());
	glVertex2d(a.getX(),a.getY());
	glVertex2d(b.getX(),b.getY());
	glVertex2d(c.getX(),c.getY());
	glEnd();

	glPopMatrix();
}

void Triangle::update(double diffTime){
	angle += diffTime*rotationSpeed;

	if(angle > 360 || angle < -360){
		angle -= 360*((int)angle/360);
	}
}

