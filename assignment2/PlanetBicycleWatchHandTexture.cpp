/*
 * PlanetBicycleWatchHandTexture.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: rohrmann
 */

#include "PlanetBicycleWatchHandTexture.h"
#include "Bicycle.h"
#include <GL/glut.h>

PlanetBicycleWatchHandTexture::PlanetBicycleWatchHandTexture(double handLength, AngleCalculator* calculator,std::string filename,double rotationSpeed,double radius,Vector4<double> color, Object* fixpoint,Vector2<double> position, Vector2<double> velocity,double mass) : PlanetWatchHandTexture(handLength, calculator,filename,rotationSpeed,radius,color,fixpoint,position,velocity,mass){
	bicycle = new Bicycle(100.0/360*2*M_PI*radius,0.6*radius);
}

PlanetBicycleWatchHandTexture::~PlanetBicycleWatchHandTexture(){
	if(bicycle){
		delete bicycle;
	}
}

void PlanetBicycleWatchHandTexture::draw(){
	PlanetWatchHandTexture::draw();

	if(!clockMode){
		glPushMatrix();
		glTranslated(pos.getX(),pos.getY(),0);
		glRotated(angle+bicycle->getDist()/(2*M_PI*radius)*360,0,0,1);
		glTranslated(0,radius*0.5,0);
		glScaled(radius*0.6,radius*0.6,radius*0.6);
		bicycle->draw();
		glPopMatrix();
	}
	else{
		glPushMatrix();
		glRotated(-handAngle,0,0,1);
		glTranslated(0,handLength,0);
		glRotated(angle+bicycle->getDist()/(2*M_PI*radius)*360,0,0,1);
		glTranslated(0,radius*0.5,0);
		glScaled(radius*0.6,radius*0.6,radius*0.6);
		bicycle->draw();
		glPopMatrix();
	}
}

void PlanetBicycleWatchHandTexture::update(double diffTime){
	PlanetWatchHandTexture::update(diffTime);

	bicycle->update(diffTime);
}
