/*
 * RungeKutta.h
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#ifndef RUNGEKUTTA_H_
#define RUNGEKUTTA_H_

#include "Derivative.h"

/*
 * This class implements the runge kutta method to solve a differential equation numerically
 */
template<typename R>
class RungeKutta{
public:
	R rk1(double t,double stepwidth,R initialConditions, Derivative<R>* derivative);
	R rk2(double t,double stepwidth,R initialConditions, Derivative<R>* derivative);
	R rk3(double t,double stepwidth,R initialConditions, Derivative<R>* derivative);
	R rk4(double t,double stepwidth,R initialConditions, Derivative<R>* derivative);
};

/*
 * 	Schema
 * 	0	0
 * 		1
 */
template<typename R>
R RungeKutta<R>::rk1(double t,double stepwidth, R initialConditions, Derivative<R>* derivative){
	double elapsedTime = 0;
	R currentState = initialConditions;
	bool notReached = true;

	while(notReached){
		if(elapsedTime + stepwidth >= t){
			stepwidth = t-elapsedTime;
			notReached = false;
		}
		R k1 = derivative->derive(elapsedTime,currentState);
		currentState = currentState + stepwidth*k1;
		elapsedTime += stepwidth;
	}

	return currentState;
}

/**
 * 	0	0	0
 * 	1	1	0
 * 		1/2	1/2
 */
template<typename R>
R RungeKutta<R>::rk2(double t, double stepwidth, R initialConditions, Derivative<R>* derivative){
	double elapsedTime = 0;
	R currentState = initialConditions;
	bool notReached = true;

	while(notReached){
		if(elapsedTime + stepwidth >= t){
			stepwidth = t-elapsedTime;
			notReached = false;
		}
		R k1 = derivative->derive(elapsedTime,currentState);
		R k2 = derivative->derive(elapsedTime+stepwidth,currentState+stepwidth*k1);
		currentState = currentState + stepwidth*(1.0/2*k1 + 1.0/2*k2);
		elapsedTime += stepwidth;
	}

	return currentState;
}

/**
 * 	0	0	0	0
 * 	1/2	1/2	0	0
 * 	1	-1	2	0
 * 		1/6	4/6	1/6
 */
template<typename R>
R RungeKutta<R>::rk3(double t, double stepwidth, R initialConditions, Derivative<R>* derivative){
	double elapsedTime = 0;
	R currentState = initialConditions;
	bool notReached = true;

	while(notReached){
		if(elapsedTime + stepwidth >= t){
			stepwidth = t-elapsedTime;
			notReached = false;
		}
		R k1 = derivative->derive(elapsedTime,currentState);
		R k2 = derivative->derive(elapsedTime+1.0/2*stepwidth,currentState+stepwidth*1.0/2*k1);
		R k3 = derivative->derive(elapsedTime+stepwidth,currentState+stepwidth*(-1*k1+2*k2));
		currentState = currentState + stepwidth*(1.0/6*k1 + 4.0/6*k2 + 1.0/6*k3);
		elapsedTime += stepwidth;
	}

	return currentState;
}

/**
 * 	0	0	0	0	0
 * 	1/2	1/2	0	0	0
 * 	1/2	0	1/2	0	0
 * 	1	0	0	1	0
 * 		1/6	1/3	1/3	1/6
 */
template<typename R>
R RungeKutta<R>::rk4(double t, double stepwidth, R initialConditions, Derivative<R>* derivative){
	double elapsedTime = 0;
	R currentState = initialConditions;
	bool notReached = true;

	while(notReached){
		if(elapsedTime + stepwidth >= t){
			stepwidth = t-elapsedTime;
			notReached = false;
		}
		R k1 = derivative->derive(elapsedTime,currentState);
		R k2 = derivative->derive(elapsedTime+1.0/2*stepwidth,currentState+stepwidth*1.0/2*k1);
		R k3 = derivative->derive(elapsedTime+1.0/2*stepwidth,currentState+stepwidth*1.0/2*k2);
		R k4 = derivative->derive(elapsedTime+stepwidth,currentState+stepwidth*k3);
		currentState = currentState + stepwidth*(1.0/6*k1 + 1.0/3*k2 + 1.0/3*k3+ 1.0/6*k4);
		elapsedTime += stepwidth;
	}

	return currentState;
}


#endif /* RUNGEKUTTA_H_ */
