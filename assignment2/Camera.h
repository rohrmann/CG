/*
 * Camera.h
 *
 *  Created on: Feb 8, 2011
 *      Author: rohrmann
 */

#ifndef CAMERA_H_
#define CAMERA_H_

/*
 * This class represents the viewer and thus saves the translation, rotation and zoom factor
 */
class Camera{
private:
	double moveSpeedX;
	double moveSpeedY;
	double rotatationSpeed;
	double zoomSpeed;
	double angle;
	double x;
	double y;
	double scale;
public:
	Camera(double left=-1.0, double right=1.0, double bottom=-1.0, double top=1.0, double time=1.0);

	void init(double moveSpeedX, double moveSpeedY, double rotationSpeed, double zoomInSpeed);

	void setCamera();

	void moveRight(double diff);
	void moveLeft(double diff);
	void moveUp(double diff);
	void moveDown(double diff);
	void rotateLeft(double diff);
	void rotateRight(double diff);
	void zoomIn(double diff);
	void zoomOut(double diff);

	double getScale(){
		return scale;
	}

	double getX(){
		return x;
	}

	double getY(){
		return y;
	}
};

#endif /* CAMERA_H_ */
