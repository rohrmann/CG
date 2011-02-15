/*
 * Derivative.h
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#ifndef DERIVATIVE_H_
#define DERIVATIVE_H_

/*
 * this class is the base class for our right side of the differential equation for the flight path of
 * planets.
 */
template<typename T>
class Derivative{
public:
	virtual T derive(double time,T state)= 0;
};


#endif /* DERIVATIVE_H_ */
