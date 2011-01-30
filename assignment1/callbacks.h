/*
 * callbacks.h
 *
 *  Created on: Jan 26, 2011
 *      Author: rohrmann
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

class Drawer{
private:
	static const double SPEED_X=0.1;
	static const double SPEED_Y=0.1;
	static const double ROTATION=10;
	static const double SCALE=1.1;
	static double translationX;
	static double translationY;
	static double rotation;
	static double scale;
	static Drawer instance;
public:
	static void drawKochCurveWrapper(void);
	static void keyboard(unsigned char ch, int , int);
	static void reshape(int width,int height);
	static void idle();
	static void init();
	void drawKochCurve();
	void drawKochCurveHelper(int i);
};



#endif /* CALLBACKS_H_ */
