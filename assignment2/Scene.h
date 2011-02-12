/*
 * Scene.h
 *
 *  Created on: Feb 10, 2011
 *      Author: rohrmann
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Updatable.h"
#include "Drawable.h"
#include <list>
#include "Vector4.h"
#include "Vector2.h"

class Object;
class Background;
class Camera;

class Scene: public Updatable,Drawable{
private:
	Camera * camera;
	Background* background;
	Object* sun;
	std::list<Object*> objects;
public:
	Scene(Camera* camera);
	Scene();

	~Scene();
	void init();
	void update(double diffTime);
	void draw();
	Vector2<double> calcVelocity(Object* fixpoint, Vector2<double> pos, double ratio, bool clockwise = true);
};


#endif /* SCENE_H_ */
