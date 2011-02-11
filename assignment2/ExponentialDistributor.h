/*
 * ExponentialDistributor.h
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#ifndef EXPONENTIALDISTRIBUTOR_H_
#define EXPONENTIALDISTRIBUTOR_H_

#include <stdlib.h>
#include <cmath>
#include "Distributor.h"


class ExponentialDistributor: public Distributor{
private:
	double lambda;
public:
	ExponentialDistributor(double lambda){
		this->lambda = lambda;
	}
	double distribute (){
		return std::log(1-(double)rand()/RAND_MAX)/-lambda;
	}
};


#endif /* EXPONENTIALDISTRIBUTOR_H_ */
