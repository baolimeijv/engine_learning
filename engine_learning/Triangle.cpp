#include "Triangle.h"

Triangle::Triangle(const vector3& v0, const vector3& v1, const vector3& v2,
	const Color& color0, const Color& color1, const Color& color2) :v{ v0,v1,v2 },
	color{color0,color1,color2} {};
void Triangle::draw_Triangle(Framebuffer &fb)
{
	float area2 = (v[1].x - v[0].x) * (v[2].y - v[0].y) - (v[2].x - v[0].x) * (v[1].y - v[0].y);
	if (area2 <= 0) return; // 剔除顺时针或共线
	//包围壳处理边界
	int minX = std::max((int)std::min(std::min(v[0].x, v[1].x), v[2].x), 0);
	int maxX = std::min((int)std::max(std::max(v[0].x, v[1].x), v[2].x),fb.width-1);
	int minY = std::max((int)std::min(std::min(v[0].y, v[1].y), v[2].y), 0);
	int maxY = std::min((int)std::max(std::max(v[0].y, v[1].y), v[2].y), fb.height - 1);

	//点转向量
	vector3 AB = v[1] - v[0];
	vector3 AC = v[2] - v[0];
	//计算权重
	float det = AB.cross2D(AC);
	if (det == 0)return;

	for (int i = minX;i <= maxX;i++)
	{
		for (int j = minY;j <= maxY;j++)
		{
			vector3 AP = vector3(i, j, 0)-v[0];
			float alpha = AP.cross2D(AC)/det;
			float betal = AB.cross2D(AP)/det;
			float gamma = 1 - alpha - betal;
			if (alpha >= 0 && betal >= 0 && gamma >= 0)
			{
				//计算该点颜色值
				float r = alpha * color[0].r + betal * color[1].r + gamma * color[2].r;
				float g = alpha * color[0].g + betal * color[1].g + gamma * color[2].g;
				float b = alpha * color[0].b + betal * color[1].b + gamma * color[2].b;
				Color Pcolor(r,g,b);
				float z = alpha * v[0].z + betal * v[1].z + gamma * v[2].z;
				if (z < fb.get_buffer(i, j))
				{
					fb.modify_buffer(i,j,z);
					fb.put_pixel(i, j, Pcolor);
				}
				
			}
		}
	}
}