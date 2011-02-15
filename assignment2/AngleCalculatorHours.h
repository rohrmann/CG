/*
 * AngleCalculatorHours.h
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#ifndef ANGLECALCULATORHOURS_H_
#define ANGLECALCULATORHOURS_H_

#include "AngleCalculator.h"

class AngleCalculatorHours : public AngleCalculator{
public:
	double angle(std::time_t seconds);
};


#endif /* ANGLECALCULATORHOURS_H_ */
