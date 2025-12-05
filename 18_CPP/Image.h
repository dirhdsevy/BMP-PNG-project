/* File: Image.h
   Task: 18 (BMP/PNG)
   Class definition for BMP Image
   Done by: [ВАШЕ ПРІЗВИЩЕ] (Group [ВАША ГРУПА])
   Date: 05.12.2025
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
    /* Constructor */
    BmpImage(int w, int h);

    /* Fill image with color */
    void clear(Color c);

    /* Set single pixel */
    void setPixel(int x, int y, Color c);

    /* Draw rectangle */
    void drawRect(int x, int y, int w, int h, Color c);

    /* Draw circle */
    void drawCircle(int xc, int yc, int r, Color c);

    /* Save to file */
    bool save(const std::string &filename) const;

    /* Display image info to console */
    void displayInfo() const;
};

#endif