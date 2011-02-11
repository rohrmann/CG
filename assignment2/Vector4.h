/*
 * Vector4.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef VECTOR4_H_
#define VECTOR4_H_

template<typename T>
class Vector4{
private:
	T data[4];
public:
	Vector4(T x, T y, T z,T a){
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = a;
	}

	T getX(){
		return data[0];
	}

	T getY(){
		return data[1];
	}

	T getZ(){
		return data[2];
	}

	T getA(){
		return data[3];
	}

	T* getData(){
		return data;
	}
};


#endif /* VECTOR4_H_ */
