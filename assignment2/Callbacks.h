/*
 * Callbacks.h
 *
 *  Created on: Feb 8, 2011
 *      Author: rohrmann
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <ctime>
#include "Camera.h"
#include "Scene.h"

class Callbacks{
private:
	static std::clock_t lastTimeStamp;
	static Camera camera;
	static bool keys[256];
	static Scene scene;
	static bool unpolling;
public:
	static void display();
	static void idle();
	static void keyboard(unsigned char key, int x, int y);
	static void keyboardUp(unsigned char key,int x, int y);
	static void keyHandling(double diffTime);
	static void reshape(int width, int height);
	static void init();
};


#endif /* CALLBACKS_H_ */
