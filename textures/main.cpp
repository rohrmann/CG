/*
 * main.cpp
 *
 *  Created on: Feb 14, 2011
 *      Author: rohrmann
 */

#include <GL/glut.h>

unsigned int texture;

struct Image{
	int width;
	int height;
	unsigned char *data;
};

Image* createTexture(){
	Image *result = new Image;

	result->width = 128;
	result->height = 128;
	result->data = new unsigned char[result->width*result->height*4];

	for(int i =0; i< result->height; i++){
		for(int j =0; j< result->width; j++){
			result->data[i*result->width*4+j*4] = 0;
			result->data[i*result->width*4+j*4+1] = 255;
			result->data[i*result->width*4+j*4+2] = 0;
			result->data[i*result->width*4+j*4+3] = 255;
		}
	}
	return result;
}

void init(){

	Image* image = createTexture();
	glClearColor(1,1,1,1);

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->width, image->height,0,GL_RGBA,GL_UNSIGNED_BYTE,image->data);
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4d(1,0,0,1);
	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexCoord2d(0,1);
	glVertex2d(-0.5,0.5);
	glTexCoord2d(0,0);
	glVertex2d(-0.5,-0.5);
	glTexCoord2d(1,0);
	glVertex2d(0.5,-0.5);
	glTexCoord2d(1,1);
	glVertex2d(0.5,0.5);
	glDisable(GL_TEXTURE_2D);
	glEnd();

	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitWindowSize(200,200);
	glutInitWindowPosition(100,100);
	glutCreateWindow("textures");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();

	return 0;
}

