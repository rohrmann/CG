/*
 * Background.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "Updatable.h"
#include "Drawable.h"
#include "Vector4.h"
#include <list>


class Distributor;
class Star;
class Camera;

class Background : public Updatable,Drawable{
private:
	static const double SPACEEXTENSION;
	Distributor* creationDistributor;
	Distributor* xDistributor;
	Distributor* yDistributor;
	Distributor* glowingDistributor;

	Camera* camera;
	Vector4<double> color;
	std::list<Star*> stars;
	int maxStars;
public:
	Background(Camera* camera, Distributor* creationDistributor, Distributor* xDistributor, Distributor* yDistributor, Distributor* glowingDistributor,Vector4<double> color = Vector4<double>(0,0,0.5,1), int maxStars=200);
	~Background();
	void draw();
	void update(double diffTime);

	void addStar();
	void initStars();

	void switchMode(){

	}
};


#endif /* BACKGROUND_H_ */
