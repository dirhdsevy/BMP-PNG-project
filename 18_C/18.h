/* File: 18.h
   Task: 18 (BMP/PNG)
   Realization of BMP structures and prototypes
   Done by: [ВАШЕ ПРІЗВИЩЕ] (Group [ВАША ГРУПА])
   Date: 05.12.2025
*/

#ifndef LIB_18_H
#define LIB_18_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* BMP File Header Structure */
#pragma pack(push, 1)
typedef struct
{
    uint16_t bfType; // File type ("BM")
    uint32_t bfSize; // File size in bytes
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits; // Offset to image data
} BMPFileHeader;

/* BMP Info Header Structure */
typedef struct
{
    uint32_t biSize;        // Header size
    int32_t biWidth;        // Image width
    int32_t biHeight;       // Image height
    uint16_t biPlanes;      // Planes (must be 1)
    uint16_t biBitCount;    // Bits per pixel (24)
    uint32_t biCompression; // Compression type
    uint32_t biSizeImage;   // Image size in bytes
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

/* Pixel structure (Blue, Green, Red) */
typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} Pixel;

/* Image structure to hold data in memory */
typedef struct
{
    int width;
    int height;
    Pixel *data;
} Image;

/* Create empty image
   @param width - image width
   @param height - image height
   @result - pointer to Image struct
*/
Image *create_image(int width, int height);

/* Free image memory
   @param img - pointer to Image struct
*/
void free_image(Image *img);

/* Fill the whole image with one color (Background)
   @param img - pointer to Image
   @param color - fill color
*/
void clear_image(Image *img, Pixel color);

/* Save image to BMP file
   @param img - pointer to Image struct
   @param filename - name of the output file
   @result - 1 on success, 0 on failure
*/
int save_bmp(Image *img, const char *filename);

/* Display human-readable info about BMP file
   @param filename - name of the file to read
*/
void print_file_info(const char *filename);

/* Set pixel color
   @param img - pointer to Image
   @param x, y - coordinates
   @param color - Pixel color
*/
void set_pixel(Image *img, int x, int y, Pixel color);

/* Draw line using Bresenham algorithm
   @param img - pointer to Image
   @param x0, y0 - start coordinates
   @param x1, y1 - end coordinates
   @param color - line color
*/
void draw_line(Image *img, int x0, int y0, int x1, int y1, Pixel color);

/* Draw rectangle
   @param img - pointer to Image
   @param x, y - top-left coordinates
   @param w, h - width and height
   @param color - border color
*/
void draw_rect(Image *img, int x, int y, int w, int h, Pixel color);

/* Draw circle
   @param img - pointer to Image
   @param xc, yc - center coordinates
   @param r - radius
   @param color - circle color
*/
void draw_circle(Image *img, int xc, int yc, int r, Pixel color);

#endif