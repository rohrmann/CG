/*
 * Bicycle.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#include "Bicycle.h"
#include <GL/glut.h>
#include "Helper.h"
#include <iostream>
using namespace std;

Bicycle::Bicycle(double speed,double scale){
	this->scale= scale;
	this->angle = 0;
	this->speed = speed;
	this->dist = 0;
}

void Bicycle::draw(){

	glPushMatrix();

	glTranslated(2,1,0);
	glRotated(angle,0,0,1);
	Helper::drawWheel(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2,1,0);
	glRotated(angle,0,0,1);
	Helper::drawWheel(1);
	glPopMatrix();

	Vector2<double> wheel(-2,1);
	Vector2<double> frame(-1.4,2.4);
	Vector2<double> frameEnd(0.7,2.4);
	Vector2<double> pedal(frameEnd.getX(),1);
	Vector2<double> rearWheel(2,1);
	Vector2<double> saddle(0.7,2.8);
	Vector2<double> steering(-1.4,2.8);
	Vector2<double> steering2(-1.1,2.8);
	Vector2<double> saddle1(0.3,saddle.getY());
	Vector2<double> saddle2(1.0,saddle.getY());
	double radius1 = 0.4;
	double radius2 = 0.2;
	double pedalLength = 0.6;
	double pedalR = 0.2;
	Vector2<double> chainStart(pedal.getX(),pedal.getY()+radius1);
	Vector2<double> chainEnd(rearWheel.getX(),rearWheel.getY()+radius2);
	Vector2<double> chain2Start(pedal.getX(),pedal.getY()-radius1);
	Vector2<double> chain2End(rearWheel.getX(),rearWheel.getY()-radius2);

	glLineWidth(2.0);
	glColor4d(1,0,0,1);
	glBegin(GL_LINE);
	glVertex2d(wheel.getX(),wheel.getY());
	glVertex2d(frame.getX(),frame.getY());

	glVertex2d(frame.getX(),frame.getY());
	glVertex2d(frameEnd.getX(),frameEnd.getY());

	glVertex2d(frameEnd.getX(),frameEnd.getY());
	glVertex2d(pedal.getX(),pedal.getY());

	glVertex2d(pedal.getX(),pedal.getY());
	glVertex2d(frame.getX(),frame.getY());

	glVertex2d(pedal.getX(),pedal.getY());
	glVertex2d(rearWheel.getX(),rearWheel.getY());

	glVertex2d(frameEnd.getX(),frameEnd.getY());
	glVertex2d(rearWheel.getX(),rearWheel.getY());

	glVertex2d(frameEnd.getX(),frameEnd.getY());
	glVertex2d(saddle.getX(),saddle.getY());

	glVertex2d(frame.getX(),frame.getY());
	glVertex2d(steering.getX(),steering.getY());

	glEnd();

	glColor4d(1,1,1,1);
	glBegin(GL_LINE);
	glVertex2d(steering.getX(),steering.getY());
	glVertex2d(steering2.getX(),steering.getY());

	glVertex2d(saddle1.getX(),saddle1.getY());
	glVertex2d(saddle2.getX(),saddle2.getY());
	glEnd();

	glLineWidth(1.0);
	glColor4d(0.4,0.4,0.4,1);
	glBegin(GL_LINE);
	glVertex2d(chainStart.getX(),chainStart.getY());
	glVertex2d(chainEnd.getX(),chainEnd.getY());

	glVertex2d(chain2Start.getX(),chain2Start.getY());
	glVertex2d(chain2End.getX(),chain2End.getY());
	glEnd();

	glLineWidth(2.0);

	glPushMatrix();
	glTranslated(pedal.getX(),pedal.getY(),0);

	glPushMatrix();
	glColor4d(0,0,0,1);
	//let the pedals be turning
	glRotated(2*angle,0,0,1);
	glBegin(GL_LINE);

	glVertex2d(0,0);
	glVertex2d(0,pedalLength);

	glEnd();

	glTranslated(0,pedalLength,0);
	glRotated(-2*angle,0,0,1);
	//let the end of the pedals be horizontal
	glBegin(GL_LINE);
	glVertex2d(-pedalR,0);
	glVertex2d(pedalR,0);
	glEnd();

	glPopMatrix();
	glColor4d(0.4,0.4,0.4,1);
	Helper::drawCircle(0.4);

	glPushMatrix();
	glRotated(2*angle,0,0,1);
	glColor4d(0,0,0,1);
	glBegin(GL_LINE);
	glVertex2d(0,0);
	glVertex2d(0,-pedalLength);
	glEnd();

	glTranslated(0,-pedalLength,0);
	glRotated(-2*angle,0,0,1);

	glBegin(GL_LINE);
	glVertex2d(-pedalR,0);
	glVertex2d(pedalR,0);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glColor4d(0.4,0.4,0.4,1);
	glTranslated(rearWheel.getX(),rearWheel.getY(),0);
	Helper::drawCircle(0.2);
	glPopMatrix();


}

void Bicycle::update(double diffTime){
	double diffDist = diffTime * speed;

	dist += diffDist;
	angle = 360*dist/(2*M_PI*scale);

	if(angle < -360 || angle > 360){
		angle -= (int)(angle/360)*360;
	}
}
