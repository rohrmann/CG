/*
 * main.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: rohrmann
 */

#include <GL/glut.h>
#include "Callbacks.h"

int main(int argc, char ** argv){
	glutInit(&argc,argv);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 2");


	Callbacks::init();

	glutIdleFunc(Callbacks::idle);
	glutReshapeFunc(Callbacks::reshape);
	glutDisplayFunc(Callbacks::display);
	glutKeyboardFunc(Callbacks::keyboard);
	glutKeyboardUpFunc(Callbacks::keyboardUp);
	glutMainLoop();

	return 0;
}

