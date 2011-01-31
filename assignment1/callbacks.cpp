#include "callbacks.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include <GL/glut.h>
using namespace std;

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
double Drawer::currentHeight = 0;
int Drawer::currentLevel = 1;

std::list<std::pair<double,double> > Drawer::nodes;
std::list<std::pair<std::pair<double,double>,double > > Drawer::colors;

void Drawer::draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	//set camera
	glScaled(scale,scale,scale);
	glRotated(rotation,0,0,1);
	glTranslated(translationX,translationY,0);
	drawPicture();
	glPopMatrix();
	glFlush();
}

void Drawer::drawPicture(){
	//enable anti-aliasing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	drawRoundedRectangle();
	drawText();
	drawKochCurve();
	//drawSierpinskiTriangle();
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);

}

void Drawer::drawRoundedRectangle(){
	glColor3d(1,1,1);
	roundedRectangle(-0.9,-0.9,0.9,0.9,0.08);
	glColor3d(0,0,0);
	roundedRectangle(-0.87,-0.87,0.87,0.87,0.07);
}

void Drawer::roundedRectangle(double leftX, double leftY, double rightX,double rightY,double radius){
	glRectd(leftX,leftY+radius,rightX,rightY-radius);
	glRectd(leftX+radius,leftY,rightX-radius,rightY);

	glPushMatrix();
	glTranslated(leftX+radius,leftY+radius,0);
	glutSolidSphere(radius,20,10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(leftX+radius,rightY-radius,0);
	glutSolidSphere(radius,20,10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(rightX-radius,leftY+radius,0);
	glutSolidSphere(radius,20,10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(rightX-radius,rightY-radius,0);
	glutSolidSphere(radius,20,10);
	glPopMatrix();
}

void Drawer::drawText(){
	glLineWidth(2.0);
	glColor3d(1.0,1.0,1.0);
	print("Koch-Curve Animation",-0.6,0.7,0,0.0008);
}

void Drawer::print(const string& text, double x, double y,double z, double scale){
	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(scale,scale,scale);

	for(int i =0; i< text.size();i++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN,text[i]);
	}

	glPopMatrix();
}

void Drawer::init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5,0.5,-0.5,0.5,-0.5,0.5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0,0,0,1.0);
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

void Drawer::drawSierpinskiTriangle(int level){
	glBegin(GL_LINE_LOOP);
	glVertex2d(-0.25,0.866025404/2);
	glVertex2d(0.25,0.866025404/2);
	glVertex2d(0,0);
	glEnd();

	if(level >0){
		glPushMatrix();
		glTranslated(0,0.866025404/2,0);
		glScaled(1.0/2,1.0/2,1.0/2);
		drawSierpinskiTriangle(level-1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-0.25,0,0);
		glScaled(1.0/2,1.0/2,1.0/2);
		drawSierpinskiTriangle(level-1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.25,0,0);
		glScaled(1.0/2,1.0/2,1.0/2);
		drawSierpinskiTriangle(level-1);
		glPopMatrix();
	}
}

void Drawer::reshape(int width, int height){
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-0.5,0.5,-0.5,0.5,-0.5,0.5);
}

void Drawer::drawKochCurve(){
	//glDisable(GL_BLEND);
	glLineWidth(1.5);
	glColor3d(0,1,0);
	glPushMatrix();
	glTranslated(-0.25,0.144337567,0);
	glRotated(60,0,0,1);
	drawKochCurveHelper(currentLevel);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25,0.144337567,0);
	glRotated(-60,0,0,1);
	drawKochCurveHelper(currentLevel);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,-0.288675135,0);
	glRotated(180,0,0,1);
	drawKochCurveHelper(currentLevel);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,-0.288675135,0);
	glColor3d(0,1,0);
	drawSierpinskiTriangle(maxSierpinskiLevel);
	glPopMatrix();
}

void Drawer::drawKochCurveHelper(int level){
	glBegin(GL_LINE);
	glColor3d(0,1,0);
	glVertex2d(-0.5,0);
	glVertex2d(0.5,0);
	glEnd();

	if(level > 1){
		glPushMatrix();
		glTranslated(-1.0/3,0,0);
		glScaled(1.0/3,1.0/3,1.0/3);
		drawKochCurveHelper(level-1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(1.0/3,0,0);
		glScaled(1.0/3,1.0/3,1.0/3);
		drawKochCurveHelper(level-1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-1.0/12,sin(M_PI*1.0/3)*1.0/6,0);
		glRotated(60,0,0,1);
		glScaled(1.0/3,1.0/3,1.0/3);
		drawKochCurveHelper(level-1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(1.0/12,sin(M_PI*1.0/3)*1.0/6,0);
		glRotated(-60,0,0,1);
		glScaled(1.0/3,1.0/3,1.0/3);
		drawKochCurveHelper(level-1);
		glPopMatrix();

		glPushMatrix();
		glScaled(1.0/3,1.0/3,1.0/3);
		glColor3d(0,1,0);
		drawSierpinskiTriangle(3);
		glPopMatrix();
	}
	else if(level == 1){
		glBegin(GL_LINE_STRIP);
		glColor3d(1-currentHeight/maxHeight,currentHeight/maxHeight,0);
		glVertex2d(-1.0/6,0);
		glVertex2d(0,currentHeight);
		glVertex2d(1.0/6,0);
		glEnd();

		glPushMatrix();
		glScaled(1.0/3,1.0/3*currentHeight/maxHeight,1.0/3);
		drawSierpinskiTriangle(maxSierpinskiLevel);
		glPopMatrix();
	}
}
/*
void Drawer::drawKochCurve(){

	glLineWidth(1);

	std::pair<double, double> first;
	std::pair<double, double> second;
	std::pair<std::pair<double,double>,double > firstColor;
	std::pair<std::pair<double,double>,double > secondColor;

	std::list<std::pair<std::pair<double,double>,double > >::const_iterator cit = colors.begin();
	std::list<std::pair<double,double> >::const_iterator it = nodes.begin();

	second = *it;
	secondColor = *cit;

	++it;
	++cit;

	while(it != nodes.end()){
		first = second;
		firstColor = secondColor;

		second = *it;
		secondColor = *cit;

		glBegin(GL_LINE);
		glColor3d(firstColor.first.first,firstColor.first.second,firstColor.second);
		glVertex2d(first.first,first.second);
		glColor3d(secondColor.first.first,secondColor.first.second,secondColor.second);
		glVertex2d(second.first,second.second);
		glEnd();

		++it;
		++cit;
	}

	first = second;
	firstColor = secondColor;

	second = *nodes.begin();
	secondColor = *colors.begin();

	glBegin(GL_LINE);
	glColor3d(firstColor.first.first,firstColor.first.second,firstColor.second);
	glVertex2d(first.first,first.second);
	glColor3d(secondColor.first.first,secondColor.first.second,secondColor.second);
	glVertex2d(second.first,second.second);
	glEnd();
	glPopMatrix();
	glFlush();
}*/

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
			if(currentHeight >= maxHeight && currentLevel < maxLevel){
				currentLevel++;
				currentHeight = 0;
			}
			else if(currentHeight >= maxHeight && currentLevel >= maxLevel){
				increasePeaks = false;
			}
			else{
				clock_t nextTimeStamp = clock();
				clock_t diff = nextTimeStamp -lastTimeStamp;
				lastTimeStamp = nextTimeStamp;

				currentHeight += diff*SPEED_HEIGHT;

				if(currentHeight > maxHeight){
					currentHeight = maxHeight;
				}
			}
		}
		else{
			if(currentHeight == 0 && currentLevel >1){
				currentLevel--;
				currentHeight = maxHeight;
			}
			else if(currentHeight == 0 && currentLevel == 1){
				increasePeaks = true;
			}
			else{
				clock_t nextTimeStamp = clock();
				clock_t diff = nextTimeStamp -lastTimeStamp;
				lastTimeStamp = nextTimeStamp;

				currentHeight -= diff*SPEED_HEIGHT;

				if(currentHeight < 0){
					currentHeight = 0;
				}
			}
		}
		glutPostRedisplay();
	}
/*
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
					insertNodes(first,second,it,cit);
					++it;
					++cit;
				}

				first = second;
				second = nodes.front();

				insertNodes(first,second,it,cit);

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
	}*/
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

	/*
	cerr << "TranslationX:" << translationX << endl;
	cerr << "TranslationY:" << translationY << endl;
	cerr << "Scale:" << scale << endl;
	cerr << "Rotation:" << rotation << endl;
	cerr << "Animation:" << (animation ? "true" : "false") << endl;*/
}


