/*
 * PlanetWatchHandTexture.h
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#ifndef PLANETWATCHHANDTEXTURE_H_
#define PLANETWATCHHANDTEXTURE_H_

#include "PlanetTexture.h"

class AngleCalculator;

/*
 * This class is used for the time mode of the application. It represents one of the hands of the watch.
 */
class PlanetWatchHandTexture : public PlanetTexture{
protected:
	double handLength;
	double handAngle;
	AngleCalculator* calculator;
public:
	PlanetWatchHandTexture(double handLength, AngleCalculator* calculator,std::string filename,double rotationSpeed,double radius,Vector4<double> color, Object* fixpoint,Vector2<double> position, Vector2<double> velocity,double mass);
	~PlanetWatchHandTexture();

	void draw();
	void update(double diffTime);

	Vector2<double> getLightPos();

	void switchMode();
};


#endif /* PLANETWATCHHANDTEXTURE_H_ */
