#ifndef IMAGE_CLASS_H
#define IMAGE_CLASS_H

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>

struct Color { uint8_t b, g, r; };

class BmpImage {
private:
    int width, height;
    std::vector<Color> pixels;

public:
    BmpImage(int w, int h);
    void clear(Color c);
    void setPixel(int x, int y, Color c);
    void drawRect(int x, int y, int w, int h, Color c);
    void drawCircle(int xc, int yc, int r, Color c);
    bool save(const std::string &filename) const;
};

#endif