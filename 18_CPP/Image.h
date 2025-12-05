/*
 * Task: 18 (BMP/PNG)
 * Student: [Ваше Прізвище]
 * File: Image.h
 * Description: C++ Class wrapper for BMP operations
 */

#ifndef IMAGE_CLASS_H
#define IMAGE_CLASS_H

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>

struct Color
{
    uint8_t b, g, r;
};

class BmpImage
{
private:
    int width, height;
    std::vector<Color> pixels;

public:
    BmpImage(int w, int h);

    // Core
    void clear(Color c);
    void setPixel(int x, int y, Color c);
    Color getPixel(int x, int y) const;

    // Drawing
    void drawRect(int x, int y, int w, int h, Color c);
    void drawCircle(int xc, int yc, int r, Color c);

    // I/O
    bool save(const std::string &filename) const;
    bool load(const std::string &filename);

    // Visualization
    void displayInfo() const;
    void displayAscii() const;

    // PNG Stub
    bool savePng(const std::string &filename) const;
};

#endif