//
// Created by 堀内哲煕 on 2017/01/02.
//

#ifndef __AFFINE_BITMAP_H__
#define __AFFINE_BITMAP_H__

#define FILEHEADERSIZE 14
#define INFOHEADERSIZE 40
#define HEADERSIZE (FILEHEADERSIZE+INFOHEADERSIZE)

#include "img_obj.h"

Image *read_image(char *filename);

void write_image(char *filename, Image *img);

#endif /*__AFFINE_BITMAP_H__*/