#include <iostream>
#include <GL/glut.h>
#include "callbacks.h"
using namespace std;

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 1: Animated Koch-Curve");
	glutDisplayFunc(Drawer::drawKochCurveWrapper);
	glutKeyboardFunc(Drawer::keyboard);
	glutReshapeFunc(Drawer::reshape);
	glutIdleFunc(Drawer::idle);
	Drawer::init();
	glutMainLoop();

	return 0;
}
