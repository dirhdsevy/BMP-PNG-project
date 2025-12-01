#ifndef LIB_18_H
#define LIB_18_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BMPFileHeader;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Pixel;

typedef struct {
    int width;
    int height;
    Pixel *data;
} Image;

Image* create_image(int width, int height);
void free_image(Image *img);
int save_bmp(Image *img, const char *filename);

void set_pixel(Image *img, int x, int y, Pixel color);
void draw_line(Image *img, int x0, int y0, int x1, int y1, Pixel color);
void draw_rect(Image *img, int x, int y, int w, int h, Pixel color);
void draw_circle(Image *img, int xc, int yc, int r, Pixel color);

#endif