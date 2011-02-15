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
#include "AngleCalculatorHours.h"
#include "AngleCalculatorMinutes.h"
#include "AngleCalculatorSeconds.h"
#include "PlanetWatchHandTexture.h"
#include "Bicycle.h"
#include "PlanetBicycle.h"
#include "PlanetBicycleWatchHandTexture.h"
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

	Vector2<double> pos = Vector2<double>(-0.3,0.1);
	Planet* planet = new PlanetBicycle("venus.bmp",0,0.04,Vector4<double>(0,1,1,1),sun,pos,calcVelocity(sun,pos,4),1);
	objects.push_back(planet);


	pos= Vector2<double>(0,0.3);
	planet = new PlanetWatchHandTexture(0.3,new AngleCalculatorHours(),"earth.bmp",100,0.03,Vector4<double>(0,0,1,1),sun,pos,calcVelocity(sun,pos,2),0.01);
	objects.push_back(planet);

	pos= Vector2<double>(0,0.08);
	Planet* moon = new PlanetTexture("moon.bmp",36,0.02,Vector4<double>(0,0,1,1),planet,pos,calcVelocity(planet,pos,1),1);
	planet->addMoon(moon);

	pos = Vector2<double>(-0.15,-0.15);
	planet = new PlanetTexture("mars.bmp",40,0.03,Vector4<double>(0,1,0,1),sun,pos,calcVelocity(sun,pos,3.5,false),0.1);
	objects.push_back(planet);

	pos = Vector2<double>(0,0.1);
	moon = new PlanetTexture("moon2.bmp",50,0.03,Vector4<double>(0,1,0,1),planet,pos,calcVelocity(planet,pos,2,true),0.01);
	planet->addMoon(moon);

	pos = Vector2<double>(0,0.1);
	Planet* moon2 = new PlanetTexture("moon.bmp",-60,0.02,Vector4<double>(0,1,1,1),moon,pos,calcVelocity(moon,pos,1.4,false),0.01);
	planet->addMoon(moon2);

	pos = Vector2<double>(0.6,0);
	planet = new PlanetBicycleWatchHandTexture(0.6,new AngleCalculatorSeconds(),"jupiter.bmp",50,0.05,Vector4<double>(1,0,0,1),sun,pos, calcVelocity(sun,pos,1),0.2);
	objects.push_back(planet);

	pos = Vector2<double>(0,0.1);
	moon = new PlanetTexture("moon1.bmp",50,0.025,Vector4<double>(0,0,1,1),planet,pos,calcVelocity(planet,pos,1.25,false),1);
	planet->addMoon(moon);

	pos = Vector2<double>(0.2,0.2);
	planet = new PlanetTexture("merkur.bmp",120,0.02,Vector4<double>(1,1,0,1),sun,pos,calcVelocity(sun,pos,5.2),1);
	objects.push_back(planet);

	pos = Vector2<double>(-0.2,-0.4);
	planet = new PlanetWatchHandTexture(0.45,new AngleCalculatorMinutes(),"neptun.bmp",42,0.045,Vector4<double>(1,0,1,1),sun,pos,calcVelocity(sun,pos,1.4,false),1);
	objects.push_back(planet);
}

Vector2<double> Scene::calcVelocity(Object* fixpoint,Vector2<double> pos, double ratio,bool clockwise){
	if(ratio < 1){
		ratio = 1;
	}

	double epsilon = 1-1/ratio;

	Vector2<double> r = pos-fixpoint->getRelPos();
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

void Scene::switchMode(){

	if(background){
		background->switchMode();
	}

	if(sun){
		sun->switchMode();
	}

	for(std::list<Object*>::iterator it = objects.begin(); it != objects.end();++it){
		(*it)->switchMode();
	}
}
