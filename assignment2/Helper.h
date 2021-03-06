/*
 * Helper.h
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <cstring>
#include "BMP.h"
#include <GL/glut.h>
#include "Vector4.h"
#include "Vector2.h"

/*
 * Convenient class which contains some useful functions
 */
class Helper{
public:
	static void drawCircle(double radius,int segments=100);
	static void drawCircleWithTexture(GLuint texName, double radius,Vector2<double> dir,double alpha=1,int segments=100);
	static void drawHalfCircle(double radius, Vector4<double> startColor, Vector4<double> endColor, int segments=100);

	static const double GRAVITATIONALCONSTANT;

	static void print(BMP* bmp);

	static std::string format2Str(Format format);

	static GLenum format2GLformat(Format format);

	static double calcValue(double dist);

	static void drawWheel(double radius,int crossings = 10, int segments = 100);
};

#endif /* HELPER_H_ */
