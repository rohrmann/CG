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
#include <list>

class Planet : public Object{
protected:
	double radius;
	Vector4<double> color;
	Object* fixpoint;
	std::list<Planet*> moons;
public:
	Planet(double radius, Vector4<double> color, Object* fixpoint, Vector2<double> position, Vector2<double> velocity, double mass);
	~Planet();
	void draw();
	void update(double diffTime);

	Vector2<double> getLightPos(){
		return fixpoint->getLightPos()-pos;
	}

	void addMoon(Planet* moon);
};


#endif /* PLANET_H_ */
