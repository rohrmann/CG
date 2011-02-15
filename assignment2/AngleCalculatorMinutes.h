/*
 * AngleCalculatorMinutes.h
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#ifndef ANGLECALCULATORMINUTES_H_
#define ANGLECALCULATORMINUTES_H_

#include "AngleCalculator.h"

class AngleCalculatorMinutes : public AngleCalculator{
public:
	double angle(std::time_t seconds);
};


#endif /* ANGLECALCULATORMINUTES_H_ */
