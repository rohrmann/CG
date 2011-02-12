/*
 * Sun.cpp
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#include "Sun.h"
#include "RoundedTriangle.h"
#include "Distributor.h"
#include <iostream>
#include <GL/glut.h>
using namespace std;

Sun::Sun(double radius, Vector4<double> baseColor,int numberTriangles, Distributor* offset,Distributor* angleSpeed):Object(Vector2<double>(0,0),Vector2<double>(0,0),1),baseColor(baseColor){
	this->numberTriangles = numberTriangles;
	this->radius = radius;
	this->offset = offset;
	this->angleSpeed = angleSpeed;
	init();
}

Sun::~Sun(){
	for(std::list<Triangle*>::const_iterator it = triangles.begin(); it != triangles.end(); ++it){
		delete *it;
	}
}

void Sun::init(){
	Vector2<double> a(0,radius);
	Vector2<double> b(-0.866025404*radius,-0.5*radius);
	Vector2<double> c(0.866025404*radius,-0.5*radius);


	double angleOffset = 120/numberTriangles;
	double angle = 0;
	for(int i=0; i< numberTriangles;i++){
		Vector4<double> color = offset->modify(baseColor,0.0,1.0);
		color.setA(0.8*(numberTriangles-i)/numberTriangles);
		int direction = rand()%2==0?-1:1;
		double as = angleSpeed->distribute();
		Triangle *triangle = new RoundedTriangle(0.31,a,b,c,color,angle,direction*as);
		triangles.push_back(triangle);
		angle += angleOffset;
	}
}

void Sun::draw(){
	for(std::list<Triangle*>::iterator it = triangles.begin(); it != triangles.end(); ++it){
		(*it)->draw();
	}
}

void Sun::update(double diffTime){
	for(std::list<Triangle*>::iterator it = triangles.begin(); it != triangles.end(); ++it){
		(*it)->update(diffTime);
	}
}

