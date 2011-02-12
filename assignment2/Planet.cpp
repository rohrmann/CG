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
	glColor4d(color.getX(),color.getY(),color.getZ(),color.getA());
	glTranslated(pos.getX(),pos.getY(),0);
	Helper::drawCircle(radius);
	glPopMatrix();
}

void Planet::update(double diffTime){
	Vector2<Vector2<double> > initialConditions(pos,velocity);

	RungeKutta<Vector2<Vector2<double> > > solver;

	Derivative<Vector2<Vector2<double> > >* derivative = new GravitationalDerivative(fixpoint->getPos(),fixpoint->getMass(),Helper::GRAVITATIONALCONSTANT);
	Vector2<Vector2<double> > result = solver.rk4(diffTime,diffTime/100,initialConditions,derivative);

	pos = result.getX();
	velocity = result.getY();

	delete derivative;
}

