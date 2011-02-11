/*
 * Background.cpp
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#include "Background.h"
#include <GL/glut.h>
#include "Camera.h"
#include "Star.h"
#include "Distributor.h"
#include <iostream>
using namespace std;

const double Background::SPACEEXTENSION = 2;

Background::~Background(){
	std::list<Star*>::const_iterator it = stars.begin();

	for(;it != stars.end(); ++it){
		delete *it;
	}

	if(creationDistributor){
		delete creationDistributor;
	}

	if(xDistributor){
		delete xDistributor;
	}

	if(yDistributor){
		delete yDistributor;
	}

	if(glowingDistributor){
		delete glowingDistributor;
	}
}

Background::Background(Camera* camera, Distributor* creationDistributor, Distributor* xDistributor, Distributor* yDistributor, Distributor* glowingDistributor,Vector4<double> color, int maxStars): color(color){
	this->xDistributor = xDistributor;
	this->yDistributor = yDistributor;
	this->creationDistributor = creationDistributor;
	this->glowingDistributor = glowingDistributor;
	this->camera = camera;
	this->maxStars = maxStars;

	initStars();
}

void Background::initStars(){
	for(int i =0; i < maxStars/2;i++){
		addStar();
	}

	for(std::list<Star*>::iterator it = stars.begin(); it != stars.end(); ++it){
		(*it)->setElapsedTime(glowingDistributor->distribute());
	}
}

void Background::draw(){
	glClearColor(color.getX(),color.getY(),color.getZ(),color.getA());
	glClear(GL_COLOR_BUFFER_BIT);

	for(std::list<Star*>::iterator it = stars.begin(); it != stars.end();++it){
		(*it)->draw();
	}
}

void Background::addStar(){
	Vector2<double> pos(xDistributor->distribute()*SPACEEXTENSION/camera->getScale()+camera->getX(),yDistributor->distribute()*SPACEEXTENSION/camera->getScale()+camera->getY());
	Star* star = new Star(pos,glowingDistributor->distribute());
	stars.push_back(star);
}

void Background::update(double diffTime){
	double creationTime = 0;
	creationTime = creationDistributor->distribute();

	bool moreStars = creationTime < diffTime;
	while(moreStars && stars.size() < maxStars){
		addStar();
		creationTime += creationDistributor->distribute();
		if(creationTime > diffTime){
			moreStars = false;
		}
	}

	for(std::list<Star*>::iterator it = stars.begin(); it != stars.end();){
		(*it)->update(diffTime);
		if((*it)->isDead(-1/camera->getScale()+camera->getX(),1/camera->getScale()+camera->getX(),-1/camera->getScale()+camera->getY(), 1/camera->getScale()+camera->getY())){
			it = stars.erase(it);
		}
		else{
			++it;
		}
	}
}

