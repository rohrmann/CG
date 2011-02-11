/*
 * Object.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Updatable.h"
#include "Drawable.h"
#include "Vector2.h"

class Object: public Updatable, public Drawable{
protected:
	Vector2<double> pos;
	double mass;
	Vector2<double> velocity;
public:
	Object(Vector2<double> pos = Vector2<double>(0,0), Vector2<double> velocity=Vector2<double>(0,0), double mass=1);

	Vector2<double> getPos(){
		return pos;
	}

	double getMass(){
		return mass;
	}

	Vector2<double> getVelocity(){
		return velocity;
	}
};



#endif /* OBJECT_H_ */
