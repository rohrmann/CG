/*
 * Star.cpp
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#include "Star.h"
#include <cmath>
#include <GL/glut.h>

Star::Star(Vector2<double> pos, double glowingDuration): Object(pos){
	this->glowingDuration = glowingDuration;
	elapsedTime = 0;
}

Vector4<double> Star::calcColor(){
	Vector4<double> result(std::sin(elapsedTime/glowingDuration*M_PI),std::sin(elapsedTime/glowingDuration*M_PI),std::sin(elapsedTime/glowingDuration*M_PI),1);
	return result;
}

void Star::draw(){
	glBegin(GL_POINT);
	Vector4<double> color = calcColor();
	glColor4d(color.getX(),color.getY(),color.getZ(),color.getA());
	glVertex2d(pos.getX(),pos.getY());
	glEnd();
}

void Star::update(double diffTime){
	elapsedTime += diffTime;
}

bool Star::isDead(double left, double right, double bottom, double top){
	return elapsedTime > glowingDuration || this->pos.getX() < left || pos.getX() > right || pos.getY() < bottom || pos.getY() > top;
}

