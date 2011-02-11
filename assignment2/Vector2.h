/*
 * Vector2d.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <cmath>

template<typename T>

class Vector2{
private:
	T x;
	T y;
public:
	Vector2(T x, T y):x(x),y(y){

	}

	T getX(){
		return x;
	}

	T getY(){
		return y;
	}

	double length(){
		return std::sqrt(x*x+y*y);
	}

	Vector2<T> operator+(const Vector2<T>& b){
		return Vector2<T>(x+b.x,y+b.y);
	}

	void operator+=(const Vector2<T>& a){
		x+= a.x;
		y+= a.y;
	}

	void operator-=(const Vector2<T>& a){
		x-= a.x;
		y-= a.y;
	}

	Vector2<T> operator-(const Vector2<T>&a){
		return Vector2<T>(x-a.x,y-a.y);
	}
};


#endif /* VECTOR2D_H_ */
