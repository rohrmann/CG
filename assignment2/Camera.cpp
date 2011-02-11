/*
 * Camera.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: rohrmann
 */

#include "Camera.h"
#include <GL/glut.h>
#include <cmath>
using namespace std;

Camera::Camera(double left, double right, double bottom, double top, double time){
	this->init((right-left)/time,(top-bottom)/time,360/time,exp(log(2)/time));
}

void Camera::init(double moveSpeedX, double moveSpeedY, double rotationSpeed, double zoomSpeed){
	this->moveSpeedX = moveSpeedX;
	this->moveSpeedY = moveSpeedY;
	this->rotatationSpeed = rotationSpeed;
	this->zoomSpeed =  zoomSpeed;

	angle = 0;
	x = 0;
	y = 0;
	scale = 1.0;
}

void Camera::setCamera(){
	glRotated(-angle,0,0,1);
	glTranslated(-x,-y,0);
	glScaled(scale,scale,scale);
}

void Camera::moveLeft(double diff){
	x -= diff*moveSpeedX/scale;
}

void Camera::moveRight(double diff){
	x += diff*moveSpeedX/scale;
}

void Camera::moveUp(double diff){
	y += diff*moveSpeedY/scale;
}

void Camera::moveDown(double diff){
	y-= diff* moveSpeedY/scale;
}

void Camera::rotateLeft(double diff){
	angle -= diff*rotatationSpeed;
}

void Camera::rotateRight(double diff){
	angle += diff*rotatationSpeed;
}

void Camera::zoomIn(double diff){
	scale *= pow(zoomSpeed,diff);
}

void Camera::zoomOut(double diff){
	scale /= pow(zoomSpeed,diff);
}
