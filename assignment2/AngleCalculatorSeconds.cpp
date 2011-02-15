/*
 * AngleCalculatorSeconds.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: rohrmann
 */

#include "AngleCalculatorSeconds.h"

double AngleCalculatorSeconds::angle(std::time_t seconds){
	return 360/60*(seconds%60);
}
