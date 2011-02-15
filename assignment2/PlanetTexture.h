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
/*
 * This class draws a planet with a texture
 */
class PlanetTexture: public Planet{
protected:
	GLuint texture;
	double angle;
	double rotationSpeed;
public:
	PlanetTexture(std::string filename,double rotationSpeed,double radius,Vector4<double> color, Object* fixpoint,Vector2<double> position, Vector2<double> velocity,double mass);
	void draw();
	void initTexture(std::string filename);
	void update(double diffTime);
	void updateAngle(double diffTime);
	void drawPlanet(double angle,Vector2<double> transFixDir, double alpha);

	void switchMode();
};


#endif /* PLANETTEXTURE_H_ */
