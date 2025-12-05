/*
 * Task: 18 (BMP/PNG)
 * Group: [Ваша Група]
 * Student: [Ваше Прізвище]
 * File: 18.h
 * Description: Header file for BMP library. Includes structures,
 * drawing primitives, IO operations, and ASCII display.
 * Date: 05.12.2025
 */

#ifndef LIB_18_H
#define LIB_18_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* BMP File Header (14 bytes) */
#pragma pack(push, 1)
typedef struct
{
    uint16_t bfType; // Signature "BM"
    uint32_t bfSize; // File size
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits; // Offset to raster data
} BMPFileHeader;

/* BMP Info Header (40 bytes) */
typedef struct
{
    uint32_t biSize;        // Header size
    int32_t biWidth;        // Width
    int32_t biHeight;       // Height
    uint16_t biPlanes;      // 1
    uint16_t biBitCount;    // 24 (RGB)
    uint32_t biCompression; // 0 (No compression)
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

/* Pixel structure (BGR order) */
typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Pixel;

/* Image container */
typedef struct
{
    int width;
    int height;
    Pixel *data;
} Image;

/* --- Core Functions --- */
Image *create_image(int width, int height);
void free_image(Image *img);
void clear_image(Image *img, Pixel color);

/* --- I/O Functions --- */
int save_bmp(Image *img, const char *filename);
Image *read_bmp(const char *filename);
void print_file_info(const char *filename);

/* --- Visualization --- */
/* Displays image content as ASCII characters in console */
void print_ascii_art(Image *img);

/* --- PNG Stubs (Requirement) --- */
int save_png(Image *img, const char *filename);
Image *read_png(const char *filename);

/* --- Drawing Functions --- */
void set_pixel(Image *img, int x, int y, Pixel color);
void draw_line(Image *img, int x0, int y0, int x1, int y1, Pixel color);
void draw_rect(Image *img, int x, int y, int w, int h, Pixel color);
void draw_circle(Image *img, int xc, int yc, int r, Pixel color);

#endif