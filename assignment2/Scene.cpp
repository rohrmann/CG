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
#include "NormalDistributor.h"
#include "Object.h"
#include "Camera.h"
#include "Sun.h"
#include "Planet.h"
#include "PlanetTexture.h"
#include "Helper.h"
#include <fstream>
#include "BMP.h"
using namespace std;

GLuint texture;

Scene::Scene(Camera* camera){
	this->camera = camera;
}

Scene::Scene(){
	camera = NULL;
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
	sun = new Sun(0.1,Vector4<double>(1,1,0,0.7),50,new NormalDistributor(0,8),new NormalDistributor(30,1200));

	Vector2<double> pos(0,0.3);
	Object* planet = new PlanetTexture("earth.bmp",100,0.03,Vector4<double>(0,0,1,1),sun,pos,calcVelocity(sun,pos,2),1);
	objects.push_back(planet);

	pos = Vector2<double>(-0.15,-0.15);
	planet = new PlanetTexture("mars.bmp",40,0.03,Vector4<double>(0,1,0,1),sun,pos,calcVelocity(sun,pos,3.5,false),1);
	objects.push_back(planet);

	pos = Vector2<double>(0.6,0);
	planet = new PlanetTexture("jupiter.bmp",50,0.05,Vector4<double>(1,0,0,1),sun,pos, calcVelocity(sun,pos,1),1);
	objects.push_back(planet);

	pos = Vector2<double>(0.2,0.2);
	planet = new PlanetTexture("merkur.bmp",120,0.02,Vector4<double>(1,1,0,1),sun,pos,calcVelocity(sun,pos,5.2),1);
	objects.push_back(planet);

	pos = Vector2<double>(-0.3,0.1);
	planet = new PlanetTexture("venus.bmp",10,0.04,Vector4<double>(0,1,1,1),sun,pos,calcVelocity(sun,pos,4),1);
	objects.push_back(planet);

	pos = Vector2<double>(-0.2,-0.4);
	planet = new PlanetTexture("neptun.bmp",42,0.045,Vector4<double>(1,0,1,1),sun,pos,calcVelocity(sun,pos,1.4,false),1);
	objects.push_back(planet);
}

Vector2<double> Scene::calcVelocity(Object* fixpoint,Vector2<double> pos, double ratio,bool clockwise){
	if(ratio < 1){
		ratio = 1;
	}

	double epsilon = 1-1/ratio;

	Vector2<double> r = pos-fixpoint->getPos();
	Vector2<double> velo = r.orthogonal();

	if(!clockwise){
		velo *= -1;
	}

	velo = velo.normalize();

	velo *= sqrt(fixpoint->getMass()*Helper::GRAVITATIONALCONSTANT*(1+epsilon)/r.length());

	return velo;
}

void Scene::draw(){

	if(background){
		background->draw();
	}
	if(sun){
		sun->draw();
	}

	for(std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it){
		(*it)->draw();
	}
}

void Scene::update(double diffTime){

	if(background)
		background->update(diffTime);

	if(sun)
		sun->update(diffTime);

	for(std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it){
		(*it)->update(diffTime);
	}
}
