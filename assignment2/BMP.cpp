/*
 * BMP.cpp
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#include "BMP.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

BMP* BMP::load(istream & is){

	bmpfile_magic magic;
	bmpfile_header header;
	bmpfile_infoheader info;

	is.read((char*)&magic,sizeof(magic));
	is.read((char*)&header,sizeof(header));
	is.read((char*)&info,sizeof(info));

	is.seekg(header.bmp_offset,ios_base::beg);

	if(info.compress_type != BI_RGB){
		cerr << "Compression type unknown:" << info.compress_type << endl;
		return NULL;
	}

	if(info.bitspp != 32){
		cerr << "Can't handle different bits per pixel than 32. BPP:" << info.bitspp << endl;
		return NULL;
	}
	else{
		uint8_t * data = new uint8_t[4*info.width*info.height];

		is.read((char*)data,4*info.width*info.height);

		return new BMP(data,info.width,info.height,ARGB);
	}
}

BMP::BMP(uint8_t* data, unsigned int width, unsigned int height, Format format){
	this->data = data;
	this->width = width;
	this->height = height;
	this->format = format;
}

BMP::~BMP(){
	if(data){
		delete [] data;
	}
}

