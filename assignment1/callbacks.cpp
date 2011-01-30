#include "callbacks.h"
#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

Drawer Drawer::instance;

double Drawer::translationX = 0;
double Drawer::translationY = 0;
double Drawer::rotation = 0;
double Drawer::scale = 1;

void Drawer::drawKochCurveWrapper(){
	instance.drawKochCurve();
}

void Drawer::init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5,0.5,-0.5,0.5,-0.5,0.5);

	glClearColor(1.0,1.0,1.0,1.0);
	glShadeModel(GL_SMOOTH);

	cout << "Move UP/DOWN: W/S" << endl;
	cout << "Move LEFT/RIGHT: A/D" << endl;
	cout << "Rotate clockwise/anti-clockwise: E/Q" << endl;
	cout << "Zoom in/out: R/F" << endl;
}

void Drawer::reshape(int width, int height){
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5,0.5,-0.5,0.5,-0.5,0.5);
}


void Drawer::drawKochCurve(){

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
		//set camera
		glScaled(scale,scale,scale);
		glRotated(rotation,0,0,1);
		glTranslated(translationX,translationY,0);

		drawKochCurveHelper(5);
	glPopMatrix();
	glFlush();
}

void Drawer::drawKochCurveHelper(int i){
	if(i == 0){
		glBegin(GL_LINE);
		glColor3d(0,0,0);
		glVertex3d(-0.5,0,0);
		glVertex3d(0.5,0,0);
		glEnd();
	}
	else{
		glPushMatrix();
		glTranslated(-1.0/3,0,0);
		glScaled(1.0/3,1.0/3,1.0/3);
		drawKochCurveHelper(i-1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-1.0/12,sin(1.0/3*M_PI)*1.0/6,0);
		glRotated(60,0,0,1);
		glScaled(1.0/3,1.0/3,1.0/3);
		drawKochCurveHelper(i-1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(1.0/12,sin(1.0/3*M_PI)*1.0/6,0);
		glRotated(-60,0,0,1);
		glScaled(1.0/3,1.0/3,1.0/3);
		drawKochCurveHelper(i-1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(1.0/3,0,0);
		glScaled(1.0/3,1.0/3,1.0/3);
		drawKochCurveHelper(i-1);
		glPopMatrix();
	}
}

void Drawer::idle(){

}

/*
 * W - upwards
 * S - downwards
 * A - left
 * D - right
 * Q - turn left
 * E - turn right
 * R - Scale up
 * F - Scale down
 */
void Drawer::keyboard(unsigned char ch, int x, int y){
	switch(ch){
	case 'w':
		translationY -= cos(rotation/180*M_PI)*SPEED_Y/scale;
		translationX -= sin(rotation/180*M_PI)*SPEED_Y/scale;
		glutPostRedisplay();
		break;
	case 's':
		translationY += cos(rotation/180*M_PI)*SPEED_Y/scale;
		translationX += sin(rotation/180*M_PI)*SPEED_Y/scale;
		glutPostRedisplay();
		break;
	case 'a':
		translationX += cos(rotation/180*M_PI)*SPEED_X/scale;
		translationY -= sin(rotation/180*M_PI)*SPEED_X/scale;
		glutPostRedisplay();
		break;
	case 'd':
		translationX -= cos(rotation/180*M_PI)*SPEED_X/scale;
		translationY += sin(rotation/180*M_PI)*SPEED_X/scale;
		glutPostRedisplay();
		break;
	case 'q':
		rotation -= ROTATION;
		glutPostRedisplay();
		break;
	case 'e':
		rotation += ROTATION;
		glutPostRedisplay();
		break;
	case 'r':
		scale *= SCALE;
		glutPostRedisplay();
		break;
	case 'f':
		if(scale > SCALE){
			scale /= SCALE;
			glutPostRedisplay();
		}
		break;
	}
	cerr << "TranslationX:" << translationX << endl;
	cerr << "TranslationY:" << translationY << endl;
	cerr << "Scale:" << scale << endl;
	cerr << "Rotation:" << rotation << endl;
}


