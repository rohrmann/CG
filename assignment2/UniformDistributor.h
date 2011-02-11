/*
 * UniformDistributor.h
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#ifndef UNIFORMDISTRIBUTOR_H_
#define UNIFORMDISTRIBUTOR_H_

#include <stdlib.h>
#include "Distributor.h"

class UniformDistributor : public Distributor{
private:
	double min;
	double max;
public:
	UniformDistributor(double min, double max){
		this->min = min;
		this->max = max;
	}
	double distribute(){
		return (double)rand()/RAND_MAX*(max-min)+min;
	}
};


#endif /* UNIFORMDISTRIBUTOR_H_ */
