#include "Image.h"
#include <iostream>

void process(std::istream &in, BmpImage &img) {
    std::string cmd;
    int x, y, w, h, r, R, G, B;
    while (in >> cmd) {
        if (cmd == "RECT") {
            in >> x >> y >> w >> h >> R >> G >> B;
            img.drawRect(x, y, w, h, {(uint8_t)B, (uint8_t)G, (uint8_t)R});
        } else if (cmd == "CIRCLE") {
            in >> x >> y >> r >> R >> G >> B;
            img.drawCircle(x, y, r, {(uint8_t)B, (uint8_t)G, (uint8_t)R});
        }
    }
}

int main() {
    int mode;
    std::cout << "1. Console\n2. File\n> ";
    std::cin >> mode;

    BmpImage img(800, 600);
    img.clear({255, 255, 255});

    if (mode == 1) process(std::cin, img);
    else {
        std::ifstream f("18_test.dat");
        if (f) process(f, img);
    }

    img.save("output_cpp.bmp");
    std::cout << "Saved output_cpp.bmp\n";
    return 0;
}