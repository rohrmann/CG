/*
 * GravitationalDerivative.h
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#ifndef GRAVITATIONALDERIVATIVE_H_
#define GRAVITATIONALDERIVATIVE_H_

#include "Derivative.h"
#include "Vector2.h"

class GravitationalDerivative : public Derivative<Vector2<Vector2<double> > >{
private:
	double mass;
	Vector2<double> pos;
	double gravitationalConstant;
public:
	GravitationalDerivative(Vector2<double> pos, double mass, double gravitationalConstant);
	Vector2<Vector2<double> > derive(double T,Vector2<Vector2<double> > state);
};


#endif /* GRAVITATIONALDERIVATIVE_H_ */
