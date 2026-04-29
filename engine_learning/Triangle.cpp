#include "Triangle.h"
bool lightopen = true;//光照开光
bool hightlight = true;//高光开关
Triangle::Triangle(const vector3& v0, const vector3& v1, const vector3& v2,
	const Color& color0, const Color& color1, const Color& color2, const vector3& n, 
	float a0, float b0, float a1, float b1, float a2, float b2, Texture2D* tex) 
	:v{ v0,v1,v2 }, color{ color0,color1,color2 }, normal(n), uv{ {a0,b0},{a1,b1},{a2,b2} }, texture(tex) {
};
void Triangle::draw_Triangle(Framebuffer& fb, matrix4 pers)
{
	float area2 = (v[1].x - v[0].x) * (v[2].y - v[0].y) - (v[2].x - v[0].x) * (v[1].y - v[0].y);
	if (area2 <= 0) return; // 剔除顺时针或共线
	//包围壳处理边界
	int minX = std::max((int)std::min(std::min(v[0].x, v[1].x), v[2].x), 0);
	int maxX = std::min((int)std::max(std::max(v[0].x, v[1].x), v[2].x), fb.width - 1);
	int minY = std::max((int)std::min(std::min(v[0].y, v[1].y), v[2].y), 0);
	int maxY = std::min((int)std::max(std::max(v[0].y, v[1].y), v[2].y), fb.height - 1);

	//点转向量
	vector3 AB = v[1] - v[0];
	vector3 AC = v[2] - v[0];
	//计算权重
	float det = AB.cross2D(AC);
	if (det == 0)return;

	for (int i = minX; i <= maxX; i++)
	{
		for (int j = minY; j <= maxY; j++)
		{
			vector3 AP = vector3(i, j, 0) - v[0];
			float alpha = AP.cross2D(AC) / det;
			float betal = AB.cross2D(AP) / det;
			float gamma = 1 - alpha - betal;
			if (alpha >= 0 && betal >= 0 && gamma >= 0)
			{
				// 透视矫正插值
				float z0 = v[0].z, z1 = v[1].z, z2 = v[2].z;
				float invZ0 = 1.0f / z0, invZ1 = 1.0f / z1, invZ2 = 1.0f / z2;

				float invZ = alpha * invZ0 + betal * invZ1 + gamma * invZ2;
				float u_over_z = alpha * uv[0][0] * invZ0 + betal * uv[1][0] * invZ1 + gamma * uv[2][0] * invZ2;
				float v_over_z = alpha * uv[0][1] * invZ0 + betal * uv[1][1] * invZ1 + gamma * uv[2][1] * invZ2;

				float UV_u = u_over_z / invZ;
				float UV_v = v_over_z / invZ;

				// 保证UV在[0,1]范围
				UV_u = std::clamp(UV_u, 0.0f, 1.0f);
				UV_v = std::clamp(UV_v, 0.0f, 1.0f);

				Color texColor;
				if (texture)
				{
					texColor = texture->sampleTrilinear(UV_u, UV_v, 0.0f);
				}
				else
				{
					float r = alpha * color[0].r + betal * color[1].r + gamma * color[2].r;
					float g = alpha * color[0].g + betal * color[1].g + gamma * color[2].g;
					float b = alpha * color[0].b + betal * color[1].b + gamma * color[2].b;
					texColor = Color(r, g, b);
				}
				//默认为0
				float intensity = 0.0f;
				//将点（1，1，1）单位化成向量表示相机指向光源
				vector3 lightDir = vector3(1, 1, 1).normalized();
				//环境光强
				float ambient = 0.2f;
				intensity += ambient;
				if (intensity > 1.0f)intensity = 1.0f;
				if (lightopen)
				{
					//漫反射
					float diff = std::max(0.0f, normal.dot(lightDir));//如果被遮挡计算值不为0，所以与0比较
					intensity += diff;//总强度
					if (intensity > 1.0f)intensity = 1.0f;//防止亮度超过光源不合理
				}
				float z = alpha * v[0].z + betal * v[1].z + gamma * v[2].z;
				//添加高光
				if (hightlight)
				{
					//获取透视矩阵关键元素
					float m00=pers.get_m(0, 0);
					float m11 = pers.get_m(1, 1);
					float m22 = pers.get_m(2, 2);
					float m23 = pers.get_m(2, 3);
					//还原像素原坐标系坐标 屏幕--->ndc--->原坐标
					float z_ndc = 2.0f * z - 1.0f;
					float x_ndc = 2.0f * i / fb.get_w() - 1.0f;
					float y_ndc = 1.0f - 2.0f * j / fb.get_h();

					float ze = -m23 / (z_ndc + m22);
					float xe = -x_ndc * ze / m00;
					float ye = -y_ndc * ze / m11;
					//像素到相机单位向量
					vector3 p(xe, ye, ze);
					p=(vector3(0,0,0)-p).normalized();
					//半角单位向量
					vector3 halfv = (p + lightDir).normalized();
					//计算高光,负数的小数次幂无意义
					float tempDot = normal.dot(halfv);
					float Hlight=0;
					if (tempDot > 0)Hlight = powf(tempDot, 4);
					//添加高光
					intensity += Hlight;
					if (intensity > 1)intensity = 1;
				}
				//加入光照修改颜色分度
				Color finalColor=texColor* intensity;
				if (z < fb.get_buffer(i, j))
				{
					fb.modify_buffer(i, j, z);
					fb.put_pixel(i, j, finalColor);
				}
			}
		}
	}
}