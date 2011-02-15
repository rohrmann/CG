/*
 * PlanetWatchHandTexture.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#include "PlanetWatchHandTexture.h"
#include "AngleCalculator.h"

PlanetWatchHandTexture::PlanetWatchHandTexture(double handLength, AngleCalculator* calculator,std::string filename,double rotationSpeed,double radius,Vector4<double> color, Object* fixpoint,Vector2<double> position, Vector2<double> velocity,double mass): PlanetTexture(filename,rotationSpeed,radius,color,fixpoint,position,velocity,mass){
	this->handLength = handLength;
	this->calculator = calculator;
	handAngle = 0;
}

PlanetWatchHandTexture::~PlanetWatchHandTexture(){
	delete calculator;
}

void PlanetWatchHandTexture::draw(){
	if(!clockMode){
		PlanetTexture::draw();
	}
	else{
		glPushMatrix();
		glRotated(-handAngle,0,0,1);
		glTranslated(0,handLength,0);
		Vector2<double> heading(-std::sin(angle/180*M_PI),std::cos(angle/180*M_PI));
		Vector2<double> fixDir(0,-1);
		Vector2<double> transFixDir(heading.orthogonal().dot(fixDir),heading.dot(fixDir));
		drawPlanet(angle,transFixDir,1);

		glRotated(handAngle,0,0,1);
		for(std::list<Planet*>::iterator it = moons.begin(); it != moons.end(); ++it){
			(*it)->draw();
		}
		glPopMatrix();
	}
}

void PlanetWatchHandTexture::update(double diffTime){
	if(!clockMode){
		PlanetTexture::update(diffTime);
	}
	else{
		for(std::list<Planet*>::iterator it = moons.begin(); it != moons.end(); ++it){
					(*it)->update(diffTime);
		}
		updateAngle(diffTime);
		handAngle = calculator->angle(time(NULL));
	}
}

Vector2<double> PlanetWatchHandTexture::getLightPos(){
	if(!clockMode){
		return PlanetTexture::getLightPos();
	}
	else{
		return fixpoint->getLightPos() - Vector2<double>(std::sin(handAngle/180*M_PI)*handLength,std::cos(handAngle/180*M_PI)*handLength);
	}
}

void PlanetWatchHandTexture::switchMode(){
	clockMode = !clockMode;
}


