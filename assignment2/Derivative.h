/*
 * Derivative.h
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#ifndef DERIVATIVE_H_
#define DERIVATIVE_H_

template<typename T>
class Derivative{
public:
	virtual T derive(double time,T state)= 0;
};


#endif /* DERIVATIVE_H_ */
