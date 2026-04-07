#pragma once
#include "framebuffer.h"
#include <SFML/Graphics.hpp>

void draw_line(Framebuffer& fb, int x0, int y0, int x1, int y1, Color color);
void draw_line(sf::RenderWindow& window, int x0, int y0, int x1, int y1, sf::Color color);