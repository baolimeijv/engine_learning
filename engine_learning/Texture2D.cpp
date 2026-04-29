#include"Texture2D.h"

Texture2D::Texture2D(int w, int h, std::vector<Color> data) : Bwidth(w), Bhight(h) {
	mipmaps.clear();
	mipSizes.clear();
	mipSizes.push_back({ w, h });   // 原图尺寸
	mipmaps.push_back(data); // 第 0 层

	int curW = w, curH = h;
	const std::vector<Color>* src = &mipmaps[0];   // 指向上一层

	while (curW > 1 || curH > 1) {
		int nextW = std::max(1, (curW+1) / 2);
		int nextH = std::max(1, (curH+1) / 2);
		std::vector<Color> next(nextW * nextH);    // 新建容器，不追加

		for (int y = 0; y < nextH; y++) 
		{
			for (int x = 0; x < nextW; x++) 
			{
				int x0 = x * 2;
				int x1 = std::min(x0 + 1, curW - 1);
				int y0 = y * 2;
				int y1 = std::min(y0 + 1, curH - 1);

				Color c00 = (*src)[y0 * curW + x0];
				Color c01 = (*src)[y0 * curW + x1];
				Color c10 = (*src)[y1 * curW + x0];
				Color c11 = (*src)[y1 * curW + x1];

				next[y * nextW + x] = (c00 + c01 + c10 + c11) / 4;
			}
		}

		mipmaps.push_back(next);
		mipSizes.push_back({ nextW, nextH });
		src = &mipmaps.back();   // 下一轮以上一层为源
		curW = nextW;
		curH = nextH;
	}
}

Texture2D Texture2D::loadTexture(const std::string& filename)
{
	sf::Image img;
	if (!img.loadFromFile(filename))
	{
		std::cerr << "Failed to load" << filename << std::endl;
		return Texture2D();
	}
	int w = img.getSize().x;
	int h = img.getSize().y;
	std::vector<Color>data(w*h);
	for (int y = 0;y < h;y++)
	{
		for (int x = 0;x < w;x++)
		{
			sf::Color c = img.getPixel(sf::Vector2u(x,y));
			data[(h - 1 - y) * w + x] = Color(c.r, c.g, c.b);
		}
	}
	return Texture2D(w,h,data);
}

Color Texture2D::sampleTrilinear(float u, float v, float lod)
{
	if (mipmaps.empty()) return Color(0, 0, 0);

	u = std::clamp(u, 0.0f, 1.0f);
	v = std::clamp(v, 0.0f, 1.0f);
	lod = std::clamp(lod, 0.0f, (float)(mipSizes.size() - 1));
	int L0 = floor(lod);
	int L1 = std::min(L0 + 1, (int)mipSizes.size() - 1);
	float t = lod - L0;
	
	Color c0 = samplebilinear(u, v, L0);
	if (L0 == L1) return c0;
	Color c1 = samplebilinear(u, v, L1);

	// 层间线性混合
	return Color(
		(unsigned char)(c0.r + (c1.r - c0.r) * t),
		(unsigned char)(c0.g + (c1.g - c0.g) * t),
		(unsigned char)(c0.b + (c1.b - c0.b) * t)
	);
}

Color Texture2D::samplebilinear(float u, float v, int level)  {
	if (level < 0 || level >= (int)mipmaps.size()) return Color(0, 0, 0);

	const std::vector<Color>& mip = mipmaps[level];
	int w = mipSizes[level].first;
	int h = mipSizes[level].second;

	if (w <= 0 || h <= 0 || mip.empty()) return Color(0, 0, 0);

	u = std::clamp(u, 0.0f, 1.0f);
	v = std::clamp(v, 0.0f, 1.0f);

	float px = u * w - 0.5f;
	float py = v * h - 0.5f;
	int x0 = (int)floorf(px);
	int y0 = (int)floorf(py);
	int x1 = std::min(x0 + 1, w - 1);
	int y1 = std::min(y0 + 1, h - 1);
	x0 = std::max(x0, 0);
	y0 = std::max(y0, 0);

	float fx = px - x0;
	float fy = py - y0;

	Color c00 = mip[y0 * w + x0];
	Color c10 = mip[y0 * w + x1];
	Color c01 = mip[y1 * w + x0];
	Color c11 = mip[y1 * w + x1];

	// 双线性插值
	auto lerp = [](const Color& a, const Color& b, float t) -> Color {
		return Color(
			(unsigned char)(a.r + (b.r - a.r) * t),
			(unsigned char)(a.g + (b.g - a.g) * t),
			(unsigned char)(a.b + (b.b - a.b) * t)
		);
		};

	Color top = lerp(c00, c10, fx);
	Color bot = lerp(c01, c11, fx);
	return lerp(top, bot, fy);
}