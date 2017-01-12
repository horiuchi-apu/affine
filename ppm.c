//
// Created by 堀内哲煕 on 2016/12/31.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "img_obj.h"
#include "ppm.h"

Image *read_image(char *filename)
{

    int i, j;
    char format[2];
    char buf[256];
    int width, height, color;
    FILE *fp;
    Image *img;

    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "エラー: %s が読み取れません", filename);
        return NULL;
    }

    fscanf(fp, "%s", format);

    getNextToken(fp, buf);
    width = atoi(buf);

    getNextToken(fp, buf);
    height = atoi(buf);

    getNextToken(fp, buf);
    color = atoi(buf);

    if ((img = initImage(width ,height, color, format)) == NULL) {
        fclose(fp);
        fprintf(stderr, "画像の初期化に失敗しました\n");
        exit(1);
    }

    if (strcmp(format, "P6") != 0) {
        img->isColor = false;
    }

    if (img->isColor) {
        for (i = height-1; i >= 0; i--) {
            for (j = 0; j < width; j++) {
                fscanf(fp, "%d %d %d", &img->pRgb[width * i + j].r, &img->pRgb[width * i + j].b, &img->pRgb[width * i + j].g);
            }
        }
    } else {
        for (i = height-1; i >= 0; i--) {
            for (j = 0; j < width; j++) {
                fscanf(fp, "%d", &img->pRgb[width * i + j].r);
            }
        }
    }

    fclose(fp);

    return img;
}

void write_image(char *filename, Image *img)
{

    int i, j;
    int width, height;
    FILE *fp;

    if ((fp = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "エラー: %s が読み取れません", filename);
        exit(1);
    }

    width = img->width;
    height = img->height;

    fprintf(fp, "%s\n", img->format);
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "%d\n", img->color);

    if (img->isColor) {
        for (i = height-1; i >= 0; i--) {
            for (j = 0; j < width; j++) {
                fprintf(fp, "%d %d %d ", img->pRgb[width * i + j].r, img->pRgb[width * i + j].b, img->pRgb[width * i + j].g);
                if (j % 10 == 0) {
                    fprintf(fp, "\n");
                }
            }
        }
    } else {

        for (i = height-1; i >= 0; i--) {
            for (j = 0; j < width; j++) {
                fprintf(fp, "%d ", img->pRgb[width * i + j].r);
                if (j % 10 == 0) {
                    fprintf(fp, "\n");
                }
            }
        }
    }

    fclose(fp);

}

void getNextToken(FILE *fp, char *buf)
{

    while ( *buf != EOF) {
        fscanf(fp, "%s", buf);

        if (buf[0] == '#') {
            fgets(buf, 256, fp);

        } else {
            break;

        }
    }

}