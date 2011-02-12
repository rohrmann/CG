/*
 * Vector2d.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <cmath>
#include <ostream>

template<typename T>

class Vector2{
private:
	T x;
	T y;
public:
	Vector2(T x, T y):x(x),y(y){

	}

	T getX()const{
		return x;
	}

	T getY()const{
		return y;
	}

	double length(){
		return std::sqrt(x*x+y*y);
	}

	Vector2<T> operator+(const Vector2<T>& b)const{
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

	void operator*=(T value){
		x*=value;
		y*=value;
	}

	void operator/=(T value){
		x/=value;
		y/=value;
	}

	Vector2<T> normalize(){
		double length = this->length();
		return Vector2<T>(x/length,y/length);
	}

	Vector2<T> operator-(const Vector2<T>&a)const{
		return Vector2<T>(x-a.x,y-a.y);
	}

	Vector2<T> operator/(T value)const{
		return Vector2<T>(x/value,y/value);
	}

	Vector2<T> operator*(T value)const{
		return Vector2<T>(x*value, y*value);
	}

	T operator*(const Vector2<T>& v)const{
		return x*v.x + y*v.y;
	}


	Vector2<T> orthogonal(){
		return Vector2<T>(y,-x);
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector){
	os << "(" << vector.getX() << "," << vector.getY() << ")";
	return os;
}

template<typename T,typename S>
Vector2<T> operator*(S value, const Vector2<T>&vector){
	return Vector2<T>(value*vector.getX(),value*vector.getY());
}


#endif /* VECTOR2D_H_ */
