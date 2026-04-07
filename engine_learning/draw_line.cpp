#include "draw_line.h"
#include <SFML/Graphics.hpp>
#include <cmath>

// 原有的 Framebuffer 版本（保留）
void draw_line(Framebuffer& fb, int x0, int y0, int x1, int y1, Color color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        fb.put_pixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// 新增：SFML 窗口版本的画线函数
void draw_line(sf::RenderWindow& window, int x0, int y0, int x1, int y1, sf::Color color) 
{
    sf::VertexArray line(sf::PrimitiveType::Lines, 2);
    line[0].position = sf::Vector2f(static_cast<float>(x0), static_cast<float>(y0));
    line[0].color = color;
    line[1].position = sf::Vector2f(static_cast<float>(x1), static_cast<float>(y1));
    line[1].color = color;
    window.draw(line);
}