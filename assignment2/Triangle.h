/*
 * Triangle.h
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Drawable.h"
#include "Updatable.h"
#include "Vector2.h"
#include "Vector4.h"

class Triangle: public Drawable, public Updatable{
protected:
	Vector2<double> a;
	Vector2<double> b;
	Vector2<double> c;
	Vector4<double> color;
	double rotationSpeed;
	double angle;
public:
	Triangle(Vector2<double> a,Vector2<double> b, Vector2<double> c,Vector4<double> color,double angle, double rotationSpeed);

	void draw();
	void update(double diffTime);
};


#endif /* TRIANGLE_H_ */
