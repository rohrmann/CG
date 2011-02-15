/*
 * PlanetBicycle.h
 *
 *  Created on: Feb 16, 2011
 *      Author: rohrmann
 */

#ifndef PLANETBICYCLE_H_
#define PLANETBICYCLE_H_

#include "PlanetTexture.h"

class Bicycle;

/*
 * This class represents a planet with a bicycle on the surface
 */
class PlanetBicycle : public PlanetTexture{
	Bicycle* bicycle;
public:
	PlanetBicycle(std::string filename,double rotationSpeed,double radius,Vector4<double> color, Object* fixpoint,Vector2<double> position, Vector2<double> velocity,double mass);
	~PlanetBicycle();
	void draw();
	void update(double diffTime);
};


#endif /* PLANETBICYCLE_H_ */
