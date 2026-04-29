#include "framebuffer.h"

Framebuffer::Framebuffer(int w, int h) : width(w), height(h) {
    pixels.resize(w * h);
    zbuffer.resize(w*h,std::numeric_limits<float>::infinity());//初始化为无穷大
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

Color Framebuffer::get_pixels(int x, int y)
{
    return pixels[y * width + x];
}

void Framebuffer::clear(Color c)
{
    std::fill(pixels.begin(), pixels.end(), c);
}

void Framebuffer::clearDepth()
{
    std::fill(zbuffer.begin(), zbuffer.end(), std::numeric_limits<float>::infinity());
}

float Framebuffer::get_buffer(int x,int y) const
{
    return zbuffer[y*width+x];
}

void Framebuffer::modify_buffer(int x, int y, float z)
{
    zbuffer[y * width + x] = z;
}

int Framebuffer::get_w() const
{
    return width;
}

int Framebuffer::get_h() const
{
    return height;
}



