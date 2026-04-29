#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include<algorithm>
#include<limits>
#include"Color.h"

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
    int get_w()const;
    int get_h()const;
private:
    int width, height;
    std::vector<Color> pixels;
    std::vector<float> zbuffer;//…Ó∂»ª∫≥Â
};
