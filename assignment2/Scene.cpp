/*
 * Scene.cpp
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#include "Scene.h"
#include <stdlib.h>
#include "Background.h"
#include "UniformDistributor.h"
#include "ExponentialDistributor.h"
#include "Object.h"
#include "Camera.h"

Scene::Scene(Camera* camera){
	this->camera = camera;
	init();
}

Scene::Scene(){
	camera = NULL;
	init();
}

Scene::~Scene(){
	if(sun != NULL){
		delete sun;
		sun = NULL;
	}

	if(background != NULL){
		delete background;
		background = NULL;
	}

	std::list<Object*>::const_iterator it = objects.begin();

	for(;it != objects.end(); ++it){
		delete *it;
	}
}

void Scene::init(){
	background = new Background(camera,new ExponentialDistributor(100),new UniformDistributor(-1,1),new UniformDistributor(-1,1),new ExponentialDistributor(1.0/2),Vector4<double>(0,0,0.33,1));
}

void Scene::draw(){
	if(background){
		background->draw();
	}
	if(sun){
		sun->draw();
	}
}

void Scene::update(double diffTime){

	if(background)
		background->update(diffTime);

	if(sun)
		sun->update(diffTime);
}
