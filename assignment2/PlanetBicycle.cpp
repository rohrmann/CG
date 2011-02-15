/*
 * PlanetBicycle.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: rohrmann
 */

#include "PlanetBicycle.h"
#include "Bicycle.h"

PlanetBicycle::PlanetBicycle(std::string filename,double rotationSpeed,double radius,Vector4<double> color, Object* fixpoint,Vector2<double> position, Vector2<double> velocity,double mass):PlanetTexture(filename,rotationSpeed,radius,color,fixpoint,position,velocity,mass){
	bicycle = new Bicycle(120.0/360*2*M_PI*radius,0.6*radius);
}

PlanetBicycle::~PlanetBicycle(){
	if(bicycle){
		delete bicycle;
	}
}

void PlanetBicycle::draw(){
	PlanetTexture::draw();

	glPushMatrix();
	glTranslated(pos.getX(),pos.getY(),0);
	glRotated(angle+bicycle->getDist()/(2*M_PI*radius)*360,0,0,1);
	glTranslated(0,radius*0.5,0);
	glScaled(radius*0.6,radius*0.6,radius*0.6);
	bicycle->draw();
	glPopMatrix();
}

void PlanetBicycle::update(double diffTime){
	PlanetTexture::update(diffTime);

	if(!clockMode)
		bicycle->update(diffTime);
}

