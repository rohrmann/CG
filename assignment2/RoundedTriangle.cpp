/*
 * RoundedTriangle.cpp
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#include "RoundedTriangle.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

void RoundedTriangle::draw(){
	glPushMatrix();
	glRotated(angle,0,0,1);

	//draw the triangle specified by a,b,c
	glBegin(GL_POLYGON);
	glColor4d(color.getX(),color.getY(),color.getZ(),color.getA());
	glVertex2d(a.getX(),a.getY());
	glVertex2d(b.getX(),b.getY());
	glVertex2d(c.getX(),c.getY());
	glEnd();

	//calculate the piece of a circle which has to be added to each side to make the triangle convex
	std::list<Vector2<double> >* nodes = makeNodes(a,b);
	drawNodes(nodes);
	delete nodes;

	nodes = makeNodes(b,c);
	drawNodes(nodes);
	delete nodes;

	nodes = makeNodes(c,a);
	drawNodes(nodes);
	delete nodes;

	glPopMatrix();
}

void RoundedTriangle::drawNodes(std::list<Vector2<double> >*nodes){
	glBegin(GL_POLYGON);
	for(std::list<Vector2<double> >::const_iterator it = nodes->begin();it != nodes->end(); ++it){
		glVertex2d(it->getX(),it->getY());
	}
	glEnd();
}

/*
 * This method calculates the points which form a piece of a circle and form the convex triangle
 */
std::list<Vector2<double> >* RoundedTriangle::makeNodes(const Vector2<double>& a, const Vector2<double>& b){
	std::list<Vector2<double> >* result = new std::list<Vector2<double> >;

	result->push_back(a);
	if(ratio != 0){
		Vector2<double> m = (a+b)/2;
		Vector2<double> c = m + (m-a).orthogonal()*ratio;

		Vector2<double> u = c-(a+b)/2;
		double t = ((a.getX()-c.getX())*(a.getX()-c.getX())+(a.getY()-c.getY())*(a.getY()-c.getY()))/(2*(u.getX()*(a.getX()-c.getX())+u.getY()*(a.getY()-c.getY())));

		Vector2<double> d = c + u*t;

		Vector2<double> da = a-d;
		Vector2<double> db = b-d;
		double value = (db*da)/da.length()/db.length();
		if(value > 1)
			value = 1;
		if(value < -1)
			value = -1;

		double tangle = acos(value);
		double angleOffset = tangle/segments;

		double x = std::cos(angleOffset);
		double y = -std::sin(angleOffset);
		Vector2<double> lastNode = a-d;
		for(int i=0; i< segments-1;i++){
			lastNode = (lastNode*x + lastNode.orthogonal()*y);
			result->push_back(lastNode+d);
		}
	}
	result->push_back(b);

	return result;
}

RoundedTriangle::RoundedTriangle(double ratio, Vector2<double> a, Vector2<double> b, Vector2<double> c, Vector4<double> color, double angle, double angleSpeed,int segments):Triangle(a,b,c,color,angle,angleSpeed){
	this->ratio = ratio;
	this->segments = segments;
}

