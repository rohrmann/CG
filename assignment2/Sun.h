/*
 * Sun.h
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#ifndef SUN_H_
#define SUN_H_

#include "Object.h"
#include <list>
#include "Vector4.h"

class Triangle;
class Distributor;

class Sun : public Object{
private:
	int numberTriangles;
	std::list<Triangle*> triangles;
	double radius;
	Vector4<double> baseColor;
	Distributor* offset;
	Distributor* angleSpeed;
public:
	Sun(double radius, Vector4<double> baseColor,int numberTriangles, Distributor* offset,Distributor* angleSpeed);
	~Sun();
	void init();
	void draw();
	void update(double diffTime);
};


#endif /* SUN_H_ */
