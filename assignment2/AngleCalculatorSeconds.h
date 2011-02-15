/*
 * AngleCalculatorSeconds.h
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#ifndef ANGLECALCULATORSECONDS_H_
#define ANGLECALCULATORSECONDS_H_

#include "AngleCalculator.h"

class AngleCalculatorSeconds : public AngleCalculator{
public:
	double angle(std::time_t seconds);
};


#endif /* ANGLECALCULATORSECONDS_H_ */
