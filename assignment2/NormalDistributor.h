/*
 * NormalDistirbutor.h
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#ifndef NORMALDISTIRBUTOR_H_
#define NORMALDISTIRBUTOR_H_

#include "Distributor.h"
#include <cmath>

/*
 * Normal distribution
 */
class NormalDistributor : public Distributor{
private:
	double expectation;
	double variance;
	int times;
public:
	NormalDistributor(double expectation=0, double variance=1, int times = 1000){
		this->expectation = expectation;
		this->variance = variance;
		this->times = times;
	}

	double distribute(){
		return variance*standardNormalDistribution() + expectation;
	}

	double standardNormalDistribution(){
		double sum = 0;

		for(int i =0; i< times; i++){
			sum = (double)rand()/RAND_MAX-0.5;
		}

		return sum/std::sqrt(times/12);
	}
};


#endif /* NORMALDISTIRBUTOR_H_ */
