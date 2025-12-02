#include "Image.h"
#include <cmath>

BmpImage::BmpImage(int w, int h) : width(w), height(h) {
    pixels.resize(width * height, {0,0,0});
}

void BmpImage::clear(Color c) {
    std::fill(pixels.begin(), pixels.end(), c);
}

void BmpImage::setPixel(int x, int y, Color c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = c;
    }
}

void BmpImage::drawRect(int x, int y, int w, int h, Color c) {
    for(int i=x; i<=x+w; i++) { setPixel(i, y, c); setPixel(i, y+h, c); }
    for(int i=y; i<=y+h; i++) { setPixel(x, i, c); setPixel(x+w, i, c); }
}

void BmpImage::drawCircle(int xc, int yc, int r, Color c) {
    int x = 0, y = r, d = 3 - 2 * r;
    while (y >= x) {
        setPixel(xc+x, yc+y, c); setPixel(xc-x, yc+y, c);
        setPixel(xc+x, yc-y, c); setPixel(xc-x, yc-y, c);
        setPixel(xc+y, yc+x, c); setPixel(xc-y, yc+x, c);
        setPixel(xc+y, yc-x, c); setPixel(xc-y, yc-x, c);
        x++;
        if (d > 0) { y--; d = d + 4 * (x - y) + 10; }
        else       d = d + 4 * x + 6;
    }
}

#pragma pack(push, 1)
struct BMPHead { uint16_t t=0x4D42; uint32_t s; uint32_t r=0; uint32_t o=54; };
struct BMPInf { uint32_t sz=40; int32_t w, h; uint16_t p=1, b=24; uint32_t c=0, si=0, x=0, y=0, u=0, i=0; };
#pragma pack(pop)

bool BmpImage::save(const std::string &filename) const {
    std::ofstream f(filename, std::ios::binary);
    if (!f) return false;

    int pad = (4 - (width * 3) % 4) % 4;
    int dsize = (width * 3 + pad) * height;
    BMPHead fh; fh.s = 54 + dsize;
    BMPInf ih; ih.w = width; ih.h = -height; ih.si = dsize;

    f.write((char*)&fh, sizeof(fh));
    f.write((char*)&ih, sizeof(ih));

    uint8_t zeros[3] = {0};
    for (int y = 0; y < height; y++) {
        f.write((char*)&pixels[y * width], width * 3);
        f.write((char*)zeros, pad);
    }
    return true;
}