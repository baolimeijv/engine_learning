#pragma once
#include"framebuffer.h"
#include<SFML/Graphics.hpp>
#include<string>
class Texture2D
{
private:
	std::vector<std::vector<Color>>mipmaps;//√ø’≈Œ∆¿ÌÕº∆¨
	std::vector<std::pair<int, int>> mipSizes;
	int Bwidth, Bhight;
public:
	Texture2D() : Bwidth(0), Bhight(0) {};
	Texture2D(int w, int h, std::vector<Color> data);
	static Texture2D loadTexture(const std::string& filename);
	Color sampleTrilinear(float u, float v, float lod);
	Color samplebilinear(float u, float v, int level);
	float getWidth() { return Bwidth; };
	float getHight() { return Bhight; };

};