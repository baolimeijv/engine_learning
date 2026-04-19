#pragma once

#include"vector3.h"
#include"framebuffer.h"
class Triangle
{
private:
	vector3 v[3];
	Color color[3];
public:
	void draw_Triangle(Framebuffer &fb);
	Triangle(const vector3& v0, const vector3& v1, const vector3& v2,
		const Color& color0, const Color& color1, const Color& color2);
};