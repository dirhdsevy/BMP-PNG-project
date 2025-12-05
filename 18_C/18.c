/*
 * Task: 18 (BMP/PNG)
 * Student: [Ваше Прізвище]
 * File: 18.c
 * Description: Implementation of BMP logic, drawing algos, and I/O.
 */

#include "18.h"

/* --- Memory Management --- */

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

/* --- I/O Operations --- */

int save_bmp(Image *img, const char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (!f)
        return 0;

    int pad = (4 - (img->width * 3) % 4) % 4;
    int data_size = (img->width * 3 + pad) * img->height;

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

Image *read_bmp(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
        return NULL;

    BMPFileHeader fh;
    BMPInfoHeader ih;
    if (fread(&fh, sizeof(fh), 1, f) != 1)
    {
        fclose(f);
        return NULL;
    }
    if (fread(&ih, sizeof(ih), 1, f) != 1)
    {
        fclose(f);
        return NULL;
    }

    if (fh.bfType != 0x4D42)
    {
        fclose(f);
        return NULL;
    } // Not BMP

    int w = abs(ih.biWidth);
    int h = abs(ih.biHeight);
    Image *img = create_image(w, h);
    if (!img)
    {
        fclose(f);
        return NULL;
    }

    fseek(f, fh.bfOffBits, SEEK_SET);
    int pad = (4 - (w * 3) % 4) % 4;
    uint8_t skip[3];

    // Read assumes top-down or bottom-up linear reading
    for (int y = 0; y < h; y++)
    {
        fread(&img->data[y * w], sizeof(Pixel), w, f);
        if (pad > 0)
            fread(skip, 1, pad, f);
    }
    fclose(f);
    return img;
}

void print_file_info(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        printf("File not found: %s\n", filename);
        return;
    }

    BMPFileHeader fh;
    BMPInfoHeader ih;
    fread(&fh, sizeof(fh), 1, f);
    fread(&ih, sizeof(ih), 1, f);

    printf("\n[BMP INFO] File: %s\n", filename);
    printf("Size: %u bytes\n", fh.bfSize);
    printf("Resolution: %dx%d\n", abs(ih.biWidth), abs(ih.biHeight));
    printf("Bit Depth: %d bits\n", ih.biBitCount);
    fclose(f);
}

/* --- ASCII Art (Human Readable Content) --- */
void print_ascii_art(Image *img)
{
    if (!img)
        return;
    const char *symbols = " .:-=+*#%@"; // Brightness map

    printf("\n[ASCII PREVIEW (%dx%d)]\n", img->width, img->height);

    // Scale down if image is too big for console
    int step_x = (img->width > 80) ? img->width / 80 : 1;
    int step_y = (img->height > 40) ? img->height / 40 : 1;

    for (int y = 0; y < img->height; y += step_y)
    {
        for (int x = 0; x < img->width; x += step_x)
        {
            Pixel p = img->data[y * img->width + x];
            // Luminance formula
            int gray = (int)(0.11 * p.b + 0.59 * p.g + 0.3 * p.r);
            int idx = gray * 9 / 255;
            printf("%c", symbols[idx]);
        }
        printf("\n");
    }
}

/* --- PNG Stubs --- */
int save_png(Image *img, const char *filename)
{
    (void)img;
    (void)filename;
    printf("[WARNING] PNG support not implemented (requires libpng).\n");
    return 0;
}
Image *read_png(const char *filename)
{
    (void)filename;
    printf("[WARNING] PNG support not implemented (requires libpng).\n");
    return NULL;
}

/* --- Drawing --- */
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