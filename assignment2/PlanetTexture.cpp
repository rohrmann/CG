/*
 * PlanetTexture.cpp
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#include "PlanetTexture.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "BMP.h"
#include "Helper.h"
using namespace std;

PlanetTexture::PlanetTexture(std::string filename,double rotationSpeed, double radius, Vector4<double> color, Object* fixpoint, Vector2<double> position, Vector2<double> velocity, double mass): Planet(radius,color,fixpoint,position,velocity,mass){
	initTexture(filename);
	this->rotationSpeed = rotationSpeed;
	angle = 0;
}

void PlanetTexture::initTexture(std::string filename){
	ifstream is;
	is.open(filename.c_str(),ios_base::in | ios_base::binary);

	if(!is){
		cerr << "Couldn't read texture file:" << filename << endl;
		exit(1);
	}

	BMP* bmp = BMP::load(is);

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,bmp->getWidth(), bmp->getHeight(),0,GL_BGRA,GL_UNSIGNED_BYTE,bmp->getData());

	is.close();

	delete bmp;
}

void PlanetTexture::draw(){

	glPushMatrix();
	glColor4d(color.getX(),color.getY(),color.getZ(),color.getA());
	glTranslated(pos.getX(),pos.getY(),0);
	glRotated(angle,0,0,1);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	Vector2<double> heading(-std::sin(angle/180*M_PI),std::cos(angle/180*M_PI));
	Vector2<double> fixDir = (fixpoint->getPos()-pos).normalize();
	Vector2<double> transFixDir(heading.orthogonal().dot(fixDir),heading.dot(fixDir));
	Helper::drawCircleWithTexture(texture,radius,transFixDir,50);
	glPopMatrix();
}

void PlanetTexture::update(double diffTime){
	Planet::update(diffTime);

	angle += rotationSpeed*diffTime;


	if(angle < -360 || angle > 360){
		angle = angle - (int)(angle/360)*360;
	}
}
