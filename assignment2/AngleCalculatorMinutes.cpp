/*
 * AngleCalculatorMinutes.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#include "AngleCalculatorMinutes.h"

double AngleCalculatorMinutes::angle(std::time_t seconds){
	return 360/60*((seconds/60)%60);
}

