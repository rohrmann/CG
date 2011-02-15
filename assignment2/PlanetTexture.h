/*
 * PlanetTexture.h
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#ifndef PLANETTEXTURE_H_
#define PLANETTEXTURE_H_

#include "Planet.h"
#include <cstring>
#include <GL/glut.h>

class PlanetTexture: public Planet{
private:
	GLuint texture;
	double angle;
	double rotationSpeed;
public:
	PlanetTexture(std::string filename,double rotationSpeed,double radius,Vector4<double> color, Object* fixpoint,Vector2<double> position, Vector2<double> velocity,double mass);
	void draw();
	void initTexture(std::string filename);
	void update(double diffTime);
};


#endif /* PLANETTEXTURE_H_ */
