/*
 * Planet.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "Object.h"
#include "Vector4.h"

class Planet : public Object{
protected:
	double radius;
	Vector4<double> color;
	Object* fixpoint;
public:
	Planet(double radius, Vector4<double> color, Object* fixpoint, Vector2<double> position, Vector2<double> velocity, double mass);
	void draw();
	void update(double diffTime);
};


#endif /* PLANET_H_ */
