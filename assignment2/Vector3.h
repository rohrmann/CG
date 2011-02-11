/*
 * Vector3.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

template<typename T>
class Vector3{
private:
	T x;
	T y;
	T z;
public:
	Vector3(T x, T y, T z): x(x),y(y),z(z){

	}

	T getX(){
		return x;
	}

	T getY(){
		return y;
	}

	T getZ(){
		return z;
	}
};


#endif /* VECTOR3_H_ */
