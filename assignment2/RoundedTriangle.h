/*
 * RoundedTriangle.h
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#ifndef ROUNDEDTRIANGLE_H_
#define ROUNDEDTRIANGLE_H_

#include "Triangle.h"
#include <list>

/*
 * This class is used to draw convex triangles
 */
class RoundedTriangle : public Triangle{
private:
	double ratio;
	int segments;
public:
	RoundedTriangle(double ratio,Vector2<double> a, Vector2<double> b, Vector2<double> c, Vector4<double> color,double angle, double rotationSpeed,int segments=100);

	void draw();
	void drawNodes(std::list<Vector2<double> >* nodes);
	std::list<Vector2<double> >* makeNodes(const Vector2<double>& a, const Vector2<double>& b);
};

#endif /* ROUNDEDTRIANGLE_H_ */
