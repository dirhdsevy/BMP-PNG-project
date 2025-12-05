/*
 * Task: 18 (BMP/PNG)
 * Test Driver (C++)
 * Student: [Ваше Прізвище]
 */

#include "Image.h"
#include <iostream>

void process(std::istream &in, BmpImage &img)
{
    std::string cmd;
    int x, y, w, h, r, R, G, B;
    while (in >> cmd)
    {
        if (cmd == "RECT")
        {
            in >> x >> y >> w >> h >> R >> G >> B;
            img.drawRect(x, y, w, h, {(uint8_t)B, (uint8_t)G, (uint8_t)R});
        }
        else if (cmd == "CIRCLE")
        {
            in >> x >> y >> r >> R >> G >> B;
            img.drawCircle(x, y, r, {(uint8_t)B, (uint8_t)G, (uint8_t)R});
        }
    }
}

int main()
{
    int mode;
    std::cout << "=== BMP Toolkit Test (C++) ===\n";
    std::cout << "1. Generate New Image\n2. Modify Existing\n3. Show ASCII\n> ";
    std::cin >> mode;

    if (mode == 1)
    {
        BmpImage img(800, 600);
        img.clear({255, 255, 255});

        std::cout << "File input? (0/1): ";
        int use_file;
        std::cin >> use_file;

        if (use_file)
        {
            std::ifstream f("18_test.dat");
            if (f)
                process(f, img);
        }
        else
        {
            std::cout << "Enter RECT x y w h r g b...\n";
            process(std::cin, img);
        }
        img.save("output_cpp.bmp");
        std::cout << "Saved output_cpp.bmp\n";
    }
    else if (mode == 2)
    {
        BmpImage img(0, 0);
        std::string fname;
        std::cout << "Filename: ";
        std::cin >> fname;
        if (img.load(fname))
        {
            img.drawRect(10, 10, 50, 50, {0, 255, 0});
            img.save("modified_cpp.bmp");
            std::cout << "Saved modified_cpp.bmp\n";
        }
    }
    else if (mode == 3)
    {
        BmpImage img(40, 20);
        img.clear({0, 0, 0});
        img.drawCircle(20, 10, 8, {255, 255, 255});
        img.displayAscii();
    }
    return 0;
}