/*
 * AngleCalculator.h
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#ifndef ANGLECALCULATOR_H_
#define ANGLECALCULATOR_H_

#include <ctime>

class AngleCalculator{
public:
	virtual double angle(std::time_t seconds)=0;
};


#endif /* ANGLECALCULATOR_H_ */
