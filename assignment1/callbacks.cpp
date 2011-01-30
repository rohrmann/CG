#include "callbacks.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include <GL/glut.h>
using namespace std;

Drawer Drawer::instance;

double Drawer::translationX = 0;
double Drawer::translationY = 0;
double Drawer::rotation = 0;
double Drawer::scale = 1;
bool Drawer::animation =  true;
bool Drawer::insertNewNodes = true;
clock_t Drawer::lastTimeStamp = clock();
int Drawer::level = 0;
bool Drawer::deleteNodes = false;
bool Drawer::increasePeaks = true;

std::list<std::pair<double,double> > Drawer::nodes;
std::list<std::pair<std::pair<double,double>,double > > Drawer::colors;

void Drawer::drawKochCurveWrapper(){
	instance.drawKochCurve();
}

void Drawer::init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5,0.5,-0.5,0.5,-0.5,0.5);

	glClearColor(1.0,1.0,1.0,1.0);
	glShadeModel(GL_SMOOTH);

	std::pair<double,double> node1(0,0.577350269);
	std::pair<double,double> node2(-0.5,-0.288675135);
	std::pair<double,double> node3(0.5,-0.288675135);

	std::pair<double,double> colorH(0,1);
	std::pair<std::pair<double,double>,double > color1(colorH,0);
	std::pair<std::pair<double,double>,double > color2(colorH,0);
	std::pair<std::pair<double,double>, double > color3(colorH,0);

	nodes.push_back(node1);
	nodes.push_back(node2);
	nodes.push_back(node3);

	colors.push_back(color1);
	colors.push_back(color2);
	colors.push_back(color3);

	cout << "Move UP/DOWN: W/S" << endl;
	cout << "Move LEFT/RIGHT: A/D" << endl;
	cout << "Rotate clockwise/anti-clockwise: E/Q" << endl;
	cout << "Zoom in/out: R/F" << endl;
	cout << "Animation: T" << endl;
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

		glBegin(GL_LINE_LOOP);
		std::list<std::pair<std::pair<double,double>,double > >::const_iterator cit = colors.begin();
		for(std::list<std::pair<double,double> >::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
			glColor3d(cit->first.first,cit->first.second,cit->second);
			glVertex2d(it->first,it->second);
			++cit;
		}
		glEnd();
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

void Drawer::insertNodes(const std::pair<double,double>& first,const std::pair<double,double>& second,std::list<std::pair<double,double> >::iterator& it, std::list<std::pair<std::pair<double,double>,double > >::iterator& cit){
	std::pair<double,double> n1;
	std::pair<double,double> n2;
	std::pair<double,double> n3;

	std::pair<std::pair<double,double>,double > c1;
	std::pair<std::pair<double,double>,double > c2;
	std::pair<std::pair<double,double>,double > c3;

	c1.first = std::pair<double,double>(0,1);
	c1.second = 0;

	c3 = c1;

	c2.first = std::pair<double,double>(1,0);
	c2.second = 0;

	colors.insert(cit,c1);
	colors.insert(cit,c2);
	colors.insert(cit,c3);

	double dx = second.first - first.first;
	double dy = second.second - first.second;

	n1.first = first.first + 1.0/3*dx;
	n1.second = first.second +1.0/3*dy;

	n2.first = first.first + 1.0/2*dx;
	n2.second = first.second + 1.0/2*dy;

	n3.first = first.first + 2.0/3*dx;
	n3.second = first.second + 2.0/3*dy;

	nodes.insert(it,n1);
	nodes.insert(it,n2);
	nodes.insert(it,n3);
}

void Drawer::idle(){

	if(animation){
		if(increasePeaks){
			if(insertNewNodes && level < maxLevel){
				std::list<std::pair<double,double> >::iterator it = nodes.begin();
				std::pair<double,double> second = *it;
				std::pair<double,double> first;
				++it;

				std::list<std::pair<std::pair<double,double>,double > >::iterator cit = colors.begin();
				++cit;

				while(it != nodes.end()){
					first = second;
					second = *it;
					instance.insertNodes(first,second,it,cit);
					++it;
					++cit;
				}

				first = second;
				second = nodes.front();

				instance.insertNodes(first,second,it,cit);

				insertNewNodes = false;

				lastTimeStamp = clock();

				level++;
			}
			else if(insertNewNodes && level >= maxLevel){
				increasePeaks = false;
				deleteNodes = false;
			}
			else{
				clock_t nextTimeStamp = clock();
				clock_t diff = nextTimeStamp -lastTimeStamp;
				lastTimeStamp = nextTimeStamp;

				std::list<std::pair<double,double> >::iterator it = nodes.begin();
				std::list<std::pair<std::pair<double,double>,double > >::iterator cit = colors.begin();

				while(it != nodes.end()){
					++it;
					std::pair<double,double>& first = *it;
					++it;
					std::pair<double,double>& second = *it;
					++it;
					std::pair<double,double>& third = *it;
					++it;

					++cit;
					std::pair<std::pair<double,double>,double >&firstColor = *cit;
					++cit;
					std::pair<std::pair<double,double>,double >&secondColor = *cit;
					++cit;
					std::pair<std::pair<double,double>,double >&thirdColor = *cit;
					++cit;

					insertNewNodes = moveNode(first,second,third,firstColor,secondColor,thirdColor,diff);
				}
			}
		}
		else{
			if(deleteNodes){
				std::list<std::pair<double,double> >::iterator it = nodes.begin();
				std::list<std::pair<std::pair<double,double>,double > >::iterator cit = colors.begin();

				while(it != nodes.end()){
					++it;
					it = nodes.erase(it);
					it = nodes.erase(it);
					it = nodes.erase(it);
					++cit;
					cit = colors.erase(cit);
					cit = colors.erase(cit);
					cit = colors.erase(cit);
				}
				level--;
				deleteNodes = false;

				if(level == 0){
					increasePeaks = true;
				}
			}
			else{
				clock_t nextTimeStamp = clock();
				clock_t diff = nextTimeStamp -lastTimeStamp;
				lastTimeStamp = nextTimeStamp;

				std::list<std::pair<double,double> >::iterator it = nodes.begin();
				std::list<std::pair<std::pair<double,double>,double > >::iterator cit = colors.begin();

				while(it != nodes.end()){
					++it;
					std::pair<double,double>& first = *it;
					++it;
					std::pair<double,double>& second = *it;
					++it;
					std::pair<double,double>& third = *it;
					++it;

					++cit;
					std::pair<std::pair<double,double>,double >&firstColor = *cit;
					++cit;
					std::pair<std::pair<double,double>,double >&secondColor = *cit;
					++cit;
					std::pair<std::pair<double,double>,double >&thirdColor = *cit;
					++cit;

					deleteNodes = unmoveNode(first,second,third,firstColor,secondColor,thirdColor,diff);
				}
			}

		}
		glutPostRedisplay();
	}
}

bool Drawer::unmoveNode(std::pair<double,double> & first, std::pair<double,double>&second, std::pair<double,double>&third, std::pair<std::pair<double,double>,double >&firstColor, std::pair<std::pair<double,double>,double >&secondColor, std::pair<std::pair<double,double>,double >&thirdColor, clock_t diff){
	double maxDistance = cos(1.0/6*M_PI)*sqrt((first.first-third.first)*(first.first-third.first) + (first.second-third.second)*(first.second-third.second));
	double xMovement = third.second - first.second;
	double yMovement = first.first - third.first;

	second.first -= xMovement*diff*SPEED_MOVEX;
	second.second -= yMovement*diff*SPEED_MOVEY;

	double xMiddle = (first.first+third.first)/2;
	double yMiddle = (first.second+third.second)/2;

	double distance = sqrt((second.first-xMiddle)*(second.first-xMiddle)+(second.second-yMiddle)*(second.second-yMiddle));

	secondColor.first.second = (1-distance/maxDistance);
	secondColor.first.first = (distance/maxDistance);
	double side = (xMovement*(second.first-xMiddle) + yMovement*(second.second-yMiddle));
	if(side < 0){
		second.first = xMiddle;
		second.second = yMiddle;
		return true;
	}
	else
		return false;
}

bool Drawer::moveNode(std::pair<double,double> & first, std::pair<double,double>&second, std::pair<double,double>&third, std::pair<std::pair<double,double>,double >&firstColor, std::pair<std::pair<double,double>,double >&secondColor, std::pair<std::pair<double,double>,double >&thirdColor, clock_t diff){
	double maxDistance = cos(1.0/6*M_PI)*sqrt((first.first-third.first)*(first.first-third.first) + (first.second-third.second)*(first.second-third.second));
	double xMovement = third.second - first.second;
	double yMovement = first.first - third.first;

	second.first += xMovement*diff*SPEED_MOVEX;
	second.second += yMovement*diff*SPEED_MOVEY;

	double xMiddle = (first.first+third.first)/2;
	double yMiddle = (first.second+third.second)/2;

	double distance = sqrt((second.first-xMiddle)*(second.first-xMiddle)+(second.second-yMiddle)*(second.second-yMiddle));

	secondColor.first.first = (1-distance/maxDistance);
	secondColor.first.second = (distance/maxDistance);

	if(distance > maxDistance){

		double normalFac = sqrt(xMovement*xMovement + yMovement*yMovement);
		second.first = xMovement*maxDistance/normalFac+xMiddle;
		second.second = yMovement*maxDistance/normalFac+yMiddle;
		return true;
	}
	else
		return false;
}

void Drawer::printNodes(){
	std::list<std::pair<std::pair<double, double>,double > >::const_iterator cit = colors.begin();
	std::list<std::pair<double,double> >::const_iterator it = nodes.begin();
	int i =0;
	while(it != nodes.end()){
		cerr <<i++ << ":(" << it->first << "," << it->second << ") RGB(" << cit->first.first << "," << cit->first.second << "," << cit->second << ")" << endl;
		++it;
		++cit;
	}
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
		scale /= SCALE;
		glutPostRedisplay();
		break;
	case 't':
		animation = !animation;
		lastTimeStamp = clock();
		break;
	}
	cerr << "TranslationX:" << translationX << endl;
	cerr << "TranslationY:" << translationY << endl;
	cerr << "Scale:" << scale << endl;
	cerr << "Rotation:" << rotation << endl;
	cerr << "Animation:" << (animation ? "true" : "false") << endl;
}


