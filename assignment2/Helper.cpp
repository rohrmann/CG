/*
 * Helper.cpp
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#include "Helper.h"
#include <cmath>
#include "Vector2.h"
#include <iostream>
using namespace std;

const double Helper::GRAVITATIONALCONSTANT = 1;

void Helper::drawCircle(double radius, int segments){
	Vector2<double> current(radius,0);
	double angle = 2*M_PI/segments;

	double x = std::cos(angle);
	double y = -std::sin(angle);


	glBegin(GL_POLYGON);
	glVertex2d(current.getX(),current.getY());

	for(int i =0; i< segments-1;i++){
		Vector2<double> ortho = current.orthogonal();
		Vector2<double> next = x*current + y*ortho;

		glVertex2d(next.getX(),next.getY());
		current = next;
	}

	glEnd();
}

void Helper::drawLightCircle(double radius, Vector4<double> startColor, Vector4<double> endColor, Vector4<double> night,int segments){
	drawHalfCircle(radius,startColor,endColor,segments);

	glPushMatrix();

	glRotated(180,0,0,1);
	drawHalfCircle(radius,night,night,segments);

	glPopMatrix();
}

void Helper::drawHalfCircle(double radius, Vector4<double> startColor, Vector4<double> endColor,int segments){
	glBegin(GL_POLYGON);
	double angleSegment = M_PI/segments;
	double x = std::cos(angleSegment);
	double y = -std::sin(angleSegment);

	Vector2<double> current = Vector2<double>(radius,0);
	Vector4<double> color = current.getY()*startColor + (1-current.getY())*endColor;

	glColor4d(color.getX(),color.getY(),color.getZ(),color.getA());
	glVertex2d(current.getX(),current.getY());

	for(int i=0; i< segments-1;i++){
		current = x*current + y*current.orthogonal();
		color = current.getY()*startColor+ (1-current.getY())*endColor;
		glColor4d(color.getX(),color.getY(),color.getZ(),color.getA());
		glVertex2d(current.getX(),current.getY());
	}

	current = Vector2<double>(-radius,0);
	color = current.getY()*startColor+ (1-current.getY())*endColor;
	glColor4d(color.getX(),color.getY(),color.getZ(),color.getA());
	glVertex2d(current.getX(),current.getY());

	glEnd();
}

void Helper::drawCircleWithTexture(GLuint texName,double radius,Vector2<double> dir, int segments){
	Vector2<double> current(0,0);
	double angle = 2*M_PI/segments;

	double x = std::cos(angle);
	double y = -std::sin(angle);

	Vector2<double> texCoords = Vector2<double>(1,0.5);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texName);

	glBegin(GL_TRIANGLE_FAN);

	double dist = (dir.dot(current)/radius+1)/2;
	double value = calcValue(dist);
	glTexCoord2d(0.5,0.5);
	glColor4d(value,value,value,1);
	glVertex2d(current.getX(),current.getY());

	current = Vector2<double>(radius,0);
	dist = (dir.dot(current)/radius+1)/2;
	value = calcValue(dist);

	glTexCoord2d(texCoords.getX(),texCoords.getY());
	glColor4d(value,value,value,1);
	glVertex2d(current.getX(),current.getY());

	for(int i =0; i< segments;i++){
		Vector2<double> ortho = current.orthogonal();
		Vector2<double> next = x*current + y*ortho;

		texCoords = 1/(2.0*radius)*(next + Vector2<double>(radius,radius));

		dist = (dir.dot(next)/radius+1)/2;
		value = calcValue(dist);
		glColor4d(value,value,value,1);
		glTexCoord2d(texCoords.getX(),texCoords.getY());
		glVertex2d(next.getX(),next.getY());
		current = next;
	}

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

double Helper::calcValue(double dist){
	return dist;
}

void Helper::print(BMP* bmp){
	cout << "BMP: Format:" << format2Str(bmp->getFormat()) << " W:" << bmp->getWidth() << " H:" << bmp->getHeight() << endl;
}

string Helper::format2Str(Format format){
	if(format == RGB){
		return "RGB";
	}
	else if(format == ARGB){
		return "ARGB";
	}
	else{
		return "Unknown";
	}
}

GLenum Helper::format2GLformat(Format format){
	if(format == RGB){
		return GL_RGB;
	}
	else if(format== ARGB){
		return GL_RGBA;
	}
}
