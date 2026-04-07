#include "framebuffer.h"

Color::Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

Framebuffer::Framebuffer(int w, int h) : width(w), height(h) {
    pixels.resize(w * h);
}

void Framebuffer::put_pixel(int x, int y, Color c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = c;
    }
}

void Framebuffer::save_ppm(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "无法打开文件 " << filename << std::endl;
        return;
    }
    ofs << "P3\n" << width << " " << height << "\n255\n";//p3 ASCll p6 二进制
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color c = pixels[y * width + x];
            ofs << (int)c.r << " " << (int)c.g << " " << (int)c.b << " ";
        }
        ofs << "\n";
    }
}