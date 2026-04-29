#include"Color.h"
#include<iostream>
Color::Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

Color Color::operator*(const float& intensity){
    int rr = (int)(r * intensity);
    int gg = (int)(g * intensity);
    int bb = (int)(b * intensity);
    // Ç¯ÖÆµ½ 0-255
    rr = std::min(std::max(rr, 0), 255);
    gg = std::min(std::max(gg, 0), 255);
    bb = std::min(std::max(bb, 0), 255);
    return Color((unsigned char)rr, (unsigned char)gg, (unsigned char)bb);
}

Color Color::operator+(const Color& other)
{
    return Color(r+other.r, g + other.g, b + other.b);
}

Color Color::operator/(float num)
{
    return Color(r/num,g/num,b/num);
}
