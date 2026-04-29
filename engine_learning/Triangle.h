#pragma once

#include"vector3.h"
#include"framebuffer.h"
#include"matrix4.h"
#include"Texture2D.h"
class Triangle
{
private:
	vector3 v[3];
	Color color[3];
	vector3 normal;//·¨Ïß
	float uv[3][2];
	Texture2D* texture;
public:
	void draw_Triangle(Framebuffer &fb,matrix4 pers=matrix4::identity());
	Triangle(const vector3& v0, const vector3& v1, const vector3& v2,
		const Color& color0, const Color& color1, const Color& color2,const vector3&n=vector3(0,0,0), 
		float a0=0, float b0=0, float a1=0, float b1=0, float a2=0, float b2=0,Texture2D* tex = nullptr);
	void disableTexture() { texture = NULL; }
};