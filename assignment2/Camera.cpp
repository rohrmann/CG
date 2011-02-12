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
	glScaled(scale,scale,scale);
	glTranslated(-x,-y,0);

}

void Camera::moveLeft(double diff){
	x -= diff*moveSpeedX/scale*cos(angle/180*M_PI);
	y -= diff*moveSpeedY/scale*sin(angle/180*M_PI);
}

void Camera::moveRight(double diff){
	x += diff*moveSpeedX/scale*cos(angle/180*M_PI);
	y += diff*moveSpeedY/scale*sin(angle/180*M_PI);
}

void Camera::moveUp(double diff){
	y += diff*moveSpeedY/scale*cos(angle/180*M_PI);
	x += diff*moveSpeedX/scale*sin(-angle/180*M_PI);
}

void Camera::moveDown(double diff){
	y-= diff* moveSpeedY/scale*cos(angle/180*M_PI);
	x-= diff*moveSpeedX/scale*sin(-angle/180*M_PI);
}

void Camera::rotateLeft(double diff){
	angle += diff*rotatationSpeed;
}

void Camera::rotateRight(double diff){
	angle -= diff*rotatationSpeed;
}

void Camera::zoomIn(double diff){
	scale *= pow(zoomSpeed,diff);
}

void Camera::zoomOut(double diff){
	scale /= pow(zoomSpeed,diff);
}
