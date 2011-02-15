/*
 * Callbacks.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: rohrmann
 */

#include <GL/glut.h>
#include "Callbacks.h"
#include <iostream>
using namespace std;

clock_t Callbacks::lastTimeStamp = clock();

Camera Callbacks::camera;
bool Callbacks::keys[256];
Scene Callbacks::scene(&Callbacks::camera);
bool Callbacks::unpolling = false;



void Callbacks::init(){
	glClearColor(0,0,0,1);
	glShadeModel(GL_SMOOTH);
	//settings for alpha blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	for(int i = 0; i< 256;i++){
		keys[i] = false;
	}

	scene.init();

	cout << "Move UP/DOWN: W/S" << endl;
	cout << "Move LEFT/RIGHT: A/D" << endl;
	cout << "Rotate clockwise/anti-clockwise: E/Q" << endl;
	cout << "Zoom in/out: R/F" << endl;
	cout << "Toggle time mode: T" << endl;
}

void Callbacks::reshape(int width, int height){
	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Callbacks::idle(){
	clock_t currentTimeStamp = clock();
	double diffTime = (double)(currentTimeStamp - lastTimeStamp)/CLOCKS_PER_SEC;
	diffTime/=1.5;
	lastTimeStamp = currentTimeStamp;

	keyHandling(diffTime);
	scene.update(diffTime);

	glutPostRedisplay();
}

/*
 * by saving which keys are currently pressed and which not it is possible to do several camera movements
 * at the same time.
 */
void Callbacks::keyHandling(double diffTime){
	//move left
	if(keys['a'] || keys['A']){
		camera.moveLeft(diffTime);
	}

	if(keys['s'] || keys['S']){
		camera.moveDown(diffTime);
	}

	if(keys['d'] || keys['D']){
		camera.moveRight(diffTime);
	}

	if(keys['w'] || keys['W']){
		camera.moveUp(diffTime);
	}

	if(keys['q'] || keys['Q']){
		camera.rotateLeft(diffTime);
	}

	if(keys['e'] || keys['E']){
		camera.rotateRight(diffTime);
	}

	if(keys['r'] || keys['R']){
		camera.zoomIn(diffTime);
	}

	if(keys['f'] || keys['F']){
		camera.zoomOut(diffTime);
	}

	if((keys['t'] || keys['T']) && !unpolling){
		scene.switchMode();
		unpolling = true;
	}

	if(!keys['t'] && !keys['T'] && unpolling){
		unpolling = false;
	}
}

//this method saves which keys are currently pressed
void Callbacks::keyboard(unsigned char key, int x, int y){
	keys[key] = true;
}

//this method registers the key which is not pressed anymore
void Callbacks::keyboardUp(unsigned char key, int x, int y){
	keys[key] = false;
}

void Callbacks::display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	camera.setCamera();
	scene.draw();

	glPopMatrix();
	glFlush();
}

