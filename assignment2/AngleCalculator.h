/*
 * AngleCalculator.h
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#ifndef ANGLECALCULATOR_H_
#define ANGLECALCULATOR_H_

#include <ctime>

/*
 * This class is the base class of the angle calculators which are used to calculate the angle of
 * according the watch hands according to the time
 */
class AngleCalculator{
public:
	virtual double angle(std::time_t seconds)=0;
};


#endif /* ANGLECALCULATOR_H_ */
