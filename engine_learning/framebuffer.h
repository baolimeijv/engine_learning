#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include<algorithm>
#include<limits>

struct Color {
    unsigned char r, g, b;
    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
};

class Framebuffer {
public:
    friend class Triangle;
    Framebuffer(int w, int h);
    void put_pixel(int x, int y, Color c);
    void save_ppm(const std::string& filename) const;
    Color get_pixels(int x,int y);
    void clear(Color c);
    void clearDepth();
    float get_buffer(int x,int y)const;
    void modify_buffer(int x, int y, float z);
private:
    int width, height;
    std::vector<Color> pixels;
    std::vector<float> zbuffer;//…Ó∂»ª∫≥Â
};
