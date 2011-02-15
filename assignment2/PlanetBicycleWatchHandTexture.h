/*
 * PlanetBicycleWatchHandTexture.h
 *
 *  Created on: Feb 16, 2011
 *      Author: rohrmann
 */

#ifndef PLANETBICYCLEWATCHHANDTEXTURE_H_
#define PLANETBICYCLEWATCHHANDTEXTURE_H_

#include "PlanetWatchHandTexture.h"

class Bicycle;

/*
 * This class combines the bicycle with the hands of the watch
 */
class PlanetBicycleWatchHandTexture : public PlanetWatchHandTexture{
private:
	Bicycle *bicycle;
public:
	PlanetBicycleWatchHandTexture(double handLength, AngleCalculator* calculator,std::string filename,double rotationSpeed,double radius,Vector4<double> color, Object* fixpoint,Vector2<double> position, Vector2<double> velocity,double mass);
	void draw();
	void update(double diffTime);
	~PlanetBicycleWatchHandTexture();
};


#endif /* PLANETBICYCLEWATCHHANDTEXTURE_H_ */
