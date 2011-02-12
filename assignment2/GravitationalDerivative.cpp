/*
 * GravitationalDerivative.cpp
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#include "GravitationalDerivative.h"

GravitationalDerivative::GravitationalDerivative(Vector2<double> pos, double mass, double gravitationalConstant): pos(pos),mass(mass),gravitationalConstant(gravitationalConstant){

}

Vector2<Vector2<double> > GravitationalDerivative::derive(double T, Vector2<Vector2<double> > state){
	Vector2<double> diff = state.getX()-pos;
	double length = diff.length();
	return Vector2<Vector2<double> >(state.getY(),-this->gravitationalConstant*mass*diff/(length*length*length));
}
