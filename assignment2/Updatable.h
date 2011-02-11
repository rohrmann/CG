/*
 * Updatable.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef UPDATABLE_H_
#define UPDATABLE_H_

class Updatable{
public:
	virtual void update(double diffTime)=0;
};

#endif /* UPDATABLE_H_ */
