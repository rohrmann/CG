/*
 * callbacks.h
 *
 *  Created on: Jan 26, 2011
 *      Author: rohrmann
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <list>
#include <utility>
#include <ctime>

class Drawer{
private:
	static const double SPEED_MOVEX=1.0/CLOCKS_PER_SEC;
	static const double SPEED_MOVEY=1.0/CLOCKS_PER_SEC;
	static const double SPEED_X=0.1;
	static const double SPEED_Y=0.1;
	static const double ROTATION=10;
	static const double SCALE=1.1;
	static const int maxLevel = 4;
	static double translationX;
	static double translationY;
	static double rotation;
	static double scale;
	static Drawer instance;
	static bool animation;
	static bool insertNewNodes;
	static bool deleteNodes;
	static clock_t lastTimeStamp;
	static int level;
	static bool increasePeaks;

	static std::list<std::pair<double,double> > nodes;
	static std::list<std::pair<std::pair<double,double>, double > > colors;


public:
	static void drawKochCurveWrapper(void);
	static void keyboard(unsigned char ch, int , int);
	static void reshape(int width,int height);
	static void idle();
	static void init();
	static void printNodes();
	static bool unmoveNode(std::pair<double,double> & first, std::pair<double,double>&second, std::pair<double,double>&third, std::pair<std::pair<double,double>,double >&firstColor, std::pair<std::pair<double,double>,double >&secondColor, std::pair<std::pair<double,double>,double >&thirdColor, clock_t diff);
	static bool moveNode(std::pair<double,double> & first, std::pair<double,double>&second, std::pair<double,double>&third, std::pair<std::pair<double,double>,double >&firstColor, std::pair<std::pair<double,double>,double >&secondColor, std::pair<std::pair<double,double>,double >&thirdColor, clock_t diff);
	void drawKochCurve();
	void drawKochCurveHelper(int i);
	void insertNodes(const std::pair<double,double>& first, const std::pair<double,double>& second,std::list<std::pair<double,double> >::iterator& it, std::list<std::pair<std::pair<double,double>,double > >::iterator& cit);
};



#endif /* CALLBACKS_H_ */
