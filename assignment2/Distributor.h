/*
 * Distributor.h
 *
 *  Created on: Feb 11, 2011
 *      Author: rohrmann
 */

#ifndef DISTRIBUTOR_H_
#define DISTRIBUTOR_H_

/*
 * Base class for different probabilistic distributions
 */
class Distributor{
public:
	virtual double distribute()=0;

	template<typename T>
	Vector4<T> modify(const Vector4<T>& base,T min, T max){
		T x = distribute() + base.getX();
		T y = distribute() + base.getY();
		T z = distribute() + base.getZ();
		T a = distribute() + base.getA();

		if(x < min){
			x = min;
		}

		if(x > max){
			x = max;
		}

		if(y < min){
			y = min;
		}

		if(y > max){
			y = max;
		}

		if(z < min){
			z = min;
		}

		if(z > max){
			z = max;
		}

		if(a < min){
			a = min;
		}

		if(a > max){
			a = max;
		}

		return Vector4<T>(x,y,z,a);
	}
};


#endif /* DISTRIBUTOR_H_ */
