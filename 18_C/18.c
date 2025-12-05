/* File: 18.c
   Task: 18 (BMP/PNG)
   Implementation of BMP logic
   Done by: [ВАШЕ ПРІЗВИЩЕ] (Group [ВАША ГРУПА])
   Date: 05.12.2025
*/

#include "18.h"

Image *create_image(int width, int height)
{
    Image *img = (Image *)malloc(sizeof(Image));
    if (!img)
        return NULL;
    img->width = width;
    img->height = height;
    img->data = (Pixel *)calloc(width * height, sizeof(Pixel));
    return img;
}

void free_image(Image *img)
{
    if (img)
    {
        if (img->data)
            free(img->data);
        free(img);
    }
}

/* NEW: Function to fill background */
void clear_image(Image *img, Pixel color)
{
    if (!img || !img->data)
        return;
    int total = img->width * img->height;
    for (int i = 0; i < total; i++)
    {
        img->data[i] = color;
    }
}

void set_pixel(Image *img, int x, int y, Pixel color)
{
    if (img && x >= 0 && x < img->width && y >= 0 && y < img->height)
    {
        img->data[y * img->width + x] = color;
    }
}

void draw_line(Image *img, int x0, int y0, int x1, int y1, Pixel color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    while (1)
    {
        set_pixel(img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_rect(Image *img, int x, int y, int w, int h, Pixel color)
{
    draw_line(img, x, y, x + w, y, color);
    draw_line(img, x, y + h, x + w, y + h, color);
    draw_line(img, x, y, x, y + h, color);
    draw_line(img, x + w, y, x + w, y + h, color);
}

void draw_circle(Image *img, int xc, int yc, int r, Pixel color)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x)
    {
        set_pixel(img, xc + x, yc + y, color);
        set_pixel(img, xc - x, yc + y, color);
        set_pixel(img, xc + x, yc - y, color);
        set_pixel(img, xc - x, yc - y, color);
        set_pixel(img, xc + y, yc + x, color);
        set_pixel(img, xc - y, yc + x, color);
        set_pixel(img, xc + y, yc - x, color);
        set_pixel(img, xc - y, yc - x, color);
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
    }
}

int save_bmp(Image *img, const char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (!f)
        return 0;

    int pad = (4 - (img->width * 3) % 4) % 4;
    int row_size = img->width * 3 + pad;
    int data_size = row_size * img->height;

    BMPFileHeader fh = {0};
    BMPInfoHeader ih = {0};

    fh.bfType = 0x4D42; // "BM"
    fh.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + data_size;
    fh.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    ih.biSize = sizeof(BMPInfoHeader);
    ih.biWidth = img->width;
    ih.biHeight = -img->height; // Top-down
    ih.biPlanes = 1;
    ih.biBitCount = 24;
    ih.biSizeImage = data_size;

    fwrite(&fh, sizeof(fh), 1, f);
    fwrite(&ih, sizeof(ih), 1, f);

    uint8_t padding[3] = {0, 0, 0};
    for (int y = 0; y < img->height; y++)
    {
        fwrite(&img->data[y * img->width], sizeof(Pixel), img->width, f);
        fwrite(padding, 1, pad, f);
    }
    fclose(f);
    return 1;
}

void print_file_info(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        printf("Failed to open file for info: %s\n", filename);
        return;
    }
    BMPFileHeader fh;
    BMPInfoHeader ih;
    fread(&fh, sizeof(fh), 1, f);
    fread(&ih, sizeof(ih), 1, f);

    printf("\n--- BMP Info: %s ---\n", filename);
    printf("Size: %u bytes\n", fh.bfSize);
    printf("Width: %d px\n", abs(ih.biWidth));
    printf("Height: %d px\n", abs(ih.biHeight));
    printf("Bit Count: %d bits\n", ih.biBitCount);
    fclose(f);
}