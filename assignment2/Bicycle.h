/*
 * Bicycle.h
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#ifndef BICYCLE_H_
#define BICYCLE_H_

#include "Object.h"

/*
 * This class represents the bicycle and animates it
 */
class Bicycle: public Object{
private:
	double scale;
	double angle;
	double speed;
	double dist;
public:
	Bicycle(double speed,double scale = 1);
	void draw();
	void update(double diffTime);

	double getDist(){
		return dist;
	}
};


#endif /* BICYCLE_H_ */
