#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
extern "C"
{
#include "../18_C/18.h"
}

bool files_equal(const std::string &f1, const std::string &f2)
{
  std::ifstream a(f1, std::ios::binary | std::ios::ate);
  std::ifstream b(f2, std::ios::binary | std::ios::ate);
  if (a.fail() || b.fail())
    return false;
  if (a.tellg() != b.tellg())
    return false;

  a.seekg(0);
  b.seekg(0);
  return std::equal(std::istreambuf_iterator<char>(a), {}, std::istreambuf_iterator<char>(b));
}

int main()
{
  std::cout << "Running Cross-Test...\n";

  Image *c_img = create_image(100, 100);
  Pixel p = {255, 0, 0};
  draw_rect(c_img, 10, 10, 50, 50, p);
  save_bmp(c_img, "test_c.bmp");
  free_image(c_img);

  BmpImage cpp_img(100, 100);
  Color c = {255, 0, 0};
  cpp_img.drawRect(10, 10, 50, 50, c);
  cpp_img.save("test_cpp.bmp");

  if (files_equal("test_c.bmp", "test_cpp.bmp"))
  {
    std::cout << "[PASS] Files are identical!\n";
  }
  else
  {
    std::cout << "[FAIL] Files differ!\n";
  }
  return 0;
}