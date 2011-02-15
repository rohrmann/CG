/*
 * BMP.h
 *
 *  Created on: Feb 12, 2011
 *      Author: rohrmann
 */

#ifndef BMP_H_
#define BMP_H_

#include <istream>
#include <stdint.h>

struct bmpfile_magic {
  unsigned char magic[2];
};

struct bmpfile_header {
  uint32_t filesz;
  uint16_t creator1;
  uint16_t creator2;
  uint32_t bmp_offset;
};

struct bmpfile_infoheader{
  uint32_t header_sz;
  int32_t width;
  int32_t height;
  uint16_t nplanes;
  uint16_t bitspp;
  uint32_t compress_type;
  uint32_t bmp_bytesz;
  int32_t hres;
  int32_t vres;
  uint32_t ncolors;
  uint32_t nimpcolors;
};

enum bmp_compression_method {
  BI_RGB = 0,
  BI_RLE8,
  BI_RLE4,
  BI_BITFIELDS,
  BI_JPEG,
  BI_PNG,
};

enum Format{
		ARGB,RGB
};

class BMP{
private:
	uint8_t* data;
	unsigned int width;
	unsigned int height;
	enum Format format;
public:
	BMP(unsigned char* data, unsigned int width, unsigned int height, Format format);
	~BMP();
	static BMP* load(std::istream& is);

	int getWidth() const{
		return width;
	}

	int getHeight()const{
		return height;
	}

	uint8_t* getData(){
		return data;
	}

	Format getFormat(){
		return format;
	}
};


#endif /* BMP_H_ */
