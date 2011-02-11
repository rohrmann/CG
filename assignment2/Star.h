/*
 * Star.h
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#ifndef STAR_H_
#define STAR_H_

#include "Object.h"
#include "Vector4.h"

class Star: public Object{
private:
	double glowingDuration;
	double elapsedTime;
public:
	Star(Vector2<double> pos, double glowingDuration);

	void draw();
	void update(double diffTime);
	bool isDead(double left, double right, double bottom, double top);

	double getGlowingDuration(){
		return glowingDuration;
	}

	void setElapsedTime(double elapsedTime){
		this->elapsedTime = elapsedTime;
	}

	Vector4<double> calcColor();
};


#endif /* STAR_H_ */
