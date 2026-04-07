#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct Color {
    unsigned char r, g, b;
    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
};

class Framebuffer {
public:
    Framebuffer(int w, int h);
    void put_pixel(int x, int y, Color c);
    void save_ppm(const std::string& filename) const;
private:
    int width, height;
    std::vector<Color> pixels;
};
