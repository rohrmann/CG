/*
 * Planet.cpp
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#include "Planet.h"
#include "RungeKutta.h"
#include "Helper.h"
#include <GL/glut.h>
#include "GravitationalDerivative.h"
#include <iostream>
using namespace std;

Planet::Planet(double radius, Vector4<double> color,Object* fixpoint, Vector2<double> position, Vector2<double> velocity, double mass): Object(position,velocity, mass), radius(radius), color(color), fixpoint(fixpoint){

}

void Planet::draw(){
	glPushMatrix();
	glColor4d(color.getX(),color.getY(),color.getZ(),(clockMode? color.getA()*.5:color.getA()));
	glTranslated(pos.getX(),pos.getY(),0);
	Helper::drawCircle(radius);

	for(std::list<Planet*>::iterator it = moons.begin(); it != moons.end(); ++it){
		(*it)->draw();
	}

	glPopMatrix();
}

Planet::~Planet(){
	for(std::list<Planet*>::const_iterator it = moons.begin(); it != moons.end(); ++it ){
		delete *it;
	}
}

void Planet::addMoon(Planet* moon){
	moons.push_back(moon);
}

/*
 * The next position is determined by the numerical approximation of the solution of the differential
 * equation: x'' = G*m/|x|^2. The Runge-Kutta method of the 4th order is used to solve it numerically.
 */
void Planet::update(double diffTime){

	if(!clockMode){
		Vector2<Vector2<double> > initialConditions(pos,velocity);

		RungeKutta<Vector2<Vector2<double> > > solver;

		Derivative<Vector2<Vector2<double> > >* derivative = new GravitationalDerivative(fixpoint->getRelPos(),fixpoint->getMass(),Helper::GRAVITATIONALCONSTANT);
		Vector2<Vector2<double> > result = solver.rk4(diffTime,diffTime/100,initialConditions,derivative);

		pos = result.getX();
		velocity = result.getY();

		delete derivative;

		for(std::list<Planet*>::iterator it = moons.begin(); it != moons.end(); ++it){
			(*it)->update(diffTime);
		}
	}
}

