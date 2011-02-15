/*
 * AngleCalculatorHours.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#include "AngleCalculatorHours.h"

double AngleCalculatorHours::angle(std::time_t seconds){
	return 360/12*((seconds/3600)%12 +8);
}

