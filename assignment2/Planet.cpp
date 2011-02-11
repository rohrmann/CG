/*
 * Planet.cpp
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#include "Planet.h"

Planet::Planet(double radius, Vector4<double> color, Vector2<double> position, Vector2<double> velocity, double mass): Object(position,velocity, mass), radius(radius), color(color){

}

void Planet::draw(){
}

void Planet::update(double diffTime){
}

