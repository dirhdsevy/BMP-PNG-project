/*
 * Task: 18 (BMP/PNG)
 * Student: [Ваше Прізвище]
 * File: Image.cpp
 */

#include "Image.h"
#include <cmath>
#include <iomanip>

BmpImage::BmpImage(int w, int h) : width(w), height(h)
{
    pixels.resize(width * height, {0, 0, 0});
}

void BmpImage::clear(Color c)
{
    std::fill(pixels.begin(), pixels.end(), c);
}

void BmpImage::setPixel(int x, int y, Color c)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        pixels[y * width + x] = c;
    }
}

Color BmpImage::getPixel(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return pixels[y * width + x];
    return {0, 0, 0};
}

void BmpImage::drawRect(int x, int y, int w, int h, Color c)
{
    for (int i = x; i <= x + w; i++)
    {
        setPixel(i, y, c);
        setPixel(i, y + h, c);
    }
    for (int i = y; i <= y + h; i++)
    {
        setPixel(x, i, c);
        setPixel(x + w, i, c);
    }
}

void BmpImage::drawCircle(int xc, int yc, int r, Color c)
{
    int x = 0, y = r, d = 3 - 2 * r;
    while (y >= x)
    {
        setPixel(xc + x, yc + y, c);
        setPixel(xc - x, yc + y, c);
        setPixel(xc + x, yc - y, c);
        setPixel(xc - x, yc - y, c);
        setPixel(xc + y, yc + x, c);
        setPixel(xc - y, yc + x, c);
        setPixel(xc + y, yc - x, c);
        setPixel(xc - y, yc - x, c);
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

#pragma pack(push, 1)
struct BMPHead
{
    uint16_t t = 0x4D42;
    uint32_t s;
    uint32_t r = 0;
    uint32_t o = 54;
};
struct BMPInf
{
    uint32_t sz = 40;
    int32_t w, h;
    uint16_t p = 1, b = 24;
    uint32_t c = 0, si = 0, x = 0, y = 0, u = 0, i = 0;
};
#pragma pack(pop)

bool BmpImage::save(const std::string &filename) const
{
    std::ofstream f(filename, std::ios::binary);
    if (!f)
        return false;

    int pad = (4 - (width * 3) % 4) % 4;
    int dsize = (width * 3 + pad) * height;
    BMPHead fh;
    fh.s = 54 + dsize;
    BMPInf ih;
    ih.w = width;
    ih.h = -height;
    ih.si = dsize;

    f.write((char *)&fh, sizeof(fh));
    f.write((char *)&ih, sizeof(ih));

    uint8_t zeros[3] = {0};
    for (int y = 0; y < height; y++)
    {
        f.write((char *)&pixels[y * width], width * 3);
        f.write((char *)zeros, pad);
    }
    return true;
}

bool BmpImage::load(const std::string &filename)
{
    std::ifstream f(filename, std::ios::binary);
    if (!f)
        return false;

    BMPHead fh;
    BMPInf ih;
    f.read((char *)&fh, sizeof(fh));
    f.read((char *)&ih, sizeof(ih));

    if (fh.t != 0x4D42)
        return false;

    width = std::abs(ih.w);
    height = std::abs(ih.h);
    pixels.resize(width * height);

    f.seekg(fh.o);
    int pad = (4 - (width * 3) % 4) % 4;

    // Simple load assuming top-down/linear
    for (int y = 0; y < height; y++)
    {
        f.read((char *)&pixels[y * width], width * 3);
        f.ignore(pad);
    }
    return true;
}

void BmpImage::displayInfo() const
{
    std::cout << "\n[C++ INFO] Image Size: " << width << "x" << height << "\n";
}

void BmpImage::displayAscii() const
{
    const char *sym = " .:-=+*#%@";
    std::cout << "\n[ASCII PREVIEW]\n";
    int step_x = (width > 80) ? width / 80 : 1;
    int step_y = (height > 40) ? height / 40 : 1;

    for (int y = 0; y < height; y += step_y)
    {
        for (int x = 0; x < width; x += step_x)
        {
            Color c = getPixel(x, y);
            int gray = (int)(0.11 * c.b + 0.59 * c.g + 0.3 * c.r);
            std::cout << sym[gray * 9 / 255];
        }
        std::cout << "\n";
    }
}

bool BmpImage::savePng(const std::string &filename) const
{
    std::cout << "[WARN] PNG saving requires external libraries. File " << filename << " not saved.\n";
    return false;
}