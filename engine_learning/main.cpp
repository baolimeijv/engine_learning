#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "vector3.h"
#include "matrix4.h"
#include"shared_ptr.h"
#include"memory_pool.h"
#include "framebuffer.h"
#include "draw_line.h"
#include"Triangle.h"
#include<vector>
#include"Texture2D.h"

int pool_test()
{
    pool p;
    if (poolinit(&p, 100, 32) == -1)
    {
        std::cout << "内存初始化失败" << std::endl;
        return -1;
    }
    void* p1 = poolmalloc(&p);
    void* p2 = poolmalloc(&p);
    void* p3 = poolmalloc(&p);
    void* p4 = poolmalloc(&p);
    std::cout << p2 << std::endl << p4 << std::endl;
    poolfree(&p, p2);
    poolfree(&p, p4);
    void* p5 = poolmalloc(&p);
    void* p6 = poolmalloc(&p);
    std::cout << p5 << std::endl << p6 << std::endl;
    destorypool(&p);
}
void shared_ptr_test()
{
    sharedptr<test> p;
    test* t = new test(10);
    sharedptr<test> p1(t);
    sharedptr<test> p2(p1);
    p2 = p;
    std::cout << p.count_t() << std::endl;
    std::cout << p1.count_t() << std::endl;
    p1->hellow();
}
void vector3_test()
{
    vector3 a(1, 2, 3);
    vector3 b(4, 5, 6);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    vector3 sum = a + b;
    vector3 diff = a - b;
    std::cout << "a + b = " << sum << std::endl;
    std::cout << "a - b = " << diff << std::endl;

    vector3 scale = a * 2.0f;
    vector3 divide = a / 2.0f;
    std::cout << "a * 2 = " << scale << std::endl;
    std::cout << "a / 2 = " << divide << std::endl;

    vector3 c = a;
    c += b;
    std::cout << "c = a; c += b; c = " << c << std::endl;
    c = a;
    c -= b;
    std::cout << "c = a; c -= b; c = " << c << std::endl;

    float dot_val = a.dot(b);
    std::cout << "a·b = " << dot_val << std::endl;
    vector3 cross_val = a.cross(b);
    std::cout << "a × b = " << cross_val << std::endl;

    std::cout << "|a| = " << a.length() << std::endl;
    std::cout << "|b| = " << b.length() << std::endl;

    vector3 a_norm = a.normalized();
    vector3 b_norm = b.normalized();
    std::cout << "a 单位化 = " << a_norm << std::endl;
    std::cout << "b 单位化 = " << b_norm << std::endl;
    std::cout << "单位化后长度: " << a_norm.length() << ", " << b_norm.length() << std::endl;

    vector3 zero(0, 0, 0);
    vector3 zero_norm = zero.normalized();
    std::cout << "零向量单位化 = " << zero_norm << " (应返回自身)\n";

    vector3 perp = a.cross(b);
    std::cout << "\n验证 a × b 是否垂直于 a 和 b:\n";
    std::cout << "a · (a×b) = " << a.dot(perp) << " (应接近 0)\n";
    std::cout << "b · (a×b) = " << b.dot(perp) << " (应接近 0)\n";

}
void matrix4_test()
{
    matrix4 T = matrix4::translation(5, 6, 7);
    vector3 p(1, 2, 3);
    vector3 p1 = T.transformPoint(p);
    std::cout << "平移 (1,2,3) -> " << p1 << std::endl;  // 应 (6,8,10)

    // 绕 Z 轴旋转 90 度
    float angle = 3.14159f / 2;
    matrix4 R = matrix4::rotationZ(angle);
    vector3 p2 = R.transformPoint(vector3(1, 0, 0));
    std::cout << "绕Z转90° (1,0,0) -> " << p2 << std::endl;  // 应 (0,1,0)

    // 先旋转再平移
    matrix4 M = T * R;
    vector3 p3 = M.transformPoint(vector3(1, 0, 0));
    std::cout << "先旋转再平移 (1,0,0) -> " << p3 << std::endl; // 应 (5,7,7)

    // 缩放测试
    matrix4 S = matrix4::scale(2, 2, 2);
    vector3 p4 = S.transformPoint(vector3(1, 2, 3));
    std::cout << "缩放2倍 (1,2,3) -> " << p4 << std::endl; // 应 (2,4,6)
}
void draw_line_test()
{
    Framebuffer fb(800, 600);
    Color red(255, 0, 0);
    Color green(0, 255, 0);
    Color blue(0, 0, 255);

    draw_line(fb, 100, 100, 700, 500, red);
    draw_line(fb, 100, 500, 700, 100, green);
    draw_line(fb, 100, 300, 700, 300, blue);

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Line Test");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // 处理窗口事件
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // 清空窗口（黑色背景）
        window.clear(sf::Color::Black);

        // 用你的 draw_line 函数画三条不同颜色的直线

        draw_line(window, 100, 100, 700, 500, sf::Color::Red);    // 红色对角线
        draw_line(window, 100, 500, 700, 100, sf::Color::Green);  // 绿色对角线
        draw_line(window, 100, 300, 700, 300, sf::Color::Blue);   // 蓝色水平线


        // 显示绘制内容
        window.display();
    }
}
void draw_Triangle_test()
{
    const int W = 800, H = 800;
    Framebuffer fb(W, H);

    Triangle triangle1(
        vector3(100, 100, 0.5f), vector3(700, 400, 0.5f), vector3(100, 700, 0.5f),
        Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255),vector3(0,0,1)
    );

    Triangle triangle2(
        vector3(0, 100, 0.5f), vector3(800, 400, 0.5f), vector3(100, 800, 0.5f),
        Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255), vector3(0, 0, 1)
    );

    sf::RenderWindow window(sf::VideoMode({ W, H }), "Triangle Test");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        fb.clear(Color(0,0,0));
        fb.clearDepth();

        std::vector<std::vector<vector3>> heartTriangles =
        {
            //左边
            {{250,100,0} ,{410,250,0},{400,700,0}},
            {{250,100,0} ,{400,700,0},{50,400,0}},
            {{250,100,0} ,{50,400,0}, {50,200,0}},
            {{250,100,0} ,{50,200,0},{130,100,0}},
            //对称
            {{550,100,0} ,{400,700,0},{390,250,0}},
            {{550,100,0} ,{750,400,0},{400,700,0}},
            {{550,100,0} ,{750,200,0},{750,400,0}},
            {{550,100,0} ,{670,100,0},{750,200,0}},

        };
        triangle1.draw_Triangle(fb);
        triangle2.draw_Triangle(fb);
        for (auto& tri : heartTriangles) 
        {
          Triangle t(tri[0], tri[1], tri[2], Color(255,0,0), Color(255,0,0), Color(255,0,0),vector3(0,0,1));
         t.draw_Triangle(fb);
        }

        sf::Image image(sf::Vector2u(W, H));
        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x++) 
            {
                Color c = fb.get_pixels(x,y);
                image.setPixel(sf::Vector2u(x, y), sf::Color(c.r, c.g, c.b));
            }
        }

        sf::Texture texture;
        (void)texture.loadFromImage(image);
        sf::Sprite sprite(texture);
        window.draw(sprite);

        window.display();
    }
}
void rotating_cube_test()
{
    const int w = 800, h = 800;
    Framebuffer fb(w, h);
    sf::RenderWindow window(sf::VideoMode({ w, h }), "Rotating Cube");
    window.setFramerateLimit(60);

    // 顶点（局部坐标）
    vector3 cubeVertex[8] = {
        {-1,-1,-1}, { 1,-1,-1}, { 1, 1,-1}, {-1, 1,-1},  // 前面四个 (z=-1)
        {-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}, {-1, 1, 1}    // 后面四个 (z=1)
    };

    // 12 个三角形（每个面两个，逆时针绕序，从外部看）
    int cubeface[12][3] = {
        {0,1,2}, {0,2,3}, // 前面
        {5,4,7}, {5,7,6}, // 后面
        {0,4,5}, {0,5,1}, // 底面
        {2,6,7}, {2,7,3}, // 顶面
        {0,3,7}, {0,7,4}, // 左面
        {1,5,6}, {1,6,2}  // 右面
    };

    // 每个三角形的颜色
    Color cubeColors[12] =
    {
        Color(255,0,0), Color(255,0,0),   // 前面红色
        Color(0,255,0), Color(0,255,0),   // 后面绿色
        Color(0,0,255), Color(0,0,255),   // 底面蓝色
        Color(255,255,0), Color(255,255,0), // 顶面黄色
        Color(255,0,255), Color(255,0,255), // 左面紫色
        Color(0,255,255), Color(0,255,255)  // 右面青色
    };

    float angleX = 0.0f;
    float angleY = 0.0f;
    float anglev = 0.1f;
    float scale=1.0f;

    Texture2D tex = Texture2D::loadTexture("C:/Users/Yang/Pictures/Screenshots/test1.png");
    bool texopen=1;
    std::cout << "tex width: " << tex.getWidth() << std::endl;
    if (tex.getWidth() == 0) {
        std::cerr << "纹理加载失败" << std::endl;
    }

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                scale += scroll->delta * 0.1f;
                scale = std::max(0.1f, scale);
            }
        }

        fb.clear(Color(0, 0, 0));
        fb.clearDepth();

        matrix4 model = matrix4::rotationX(angleX) * matrix4::rotationY(angleY)*matrix4::scale(scale,scale,scale);
        matrix4 view = matrix4::translation(0, 0, -5);
        matrix4 proj = matrix4::perspective(3.141592f / 3, (float)w / h, 0.1f, 1000.0f);
        matrix4 mv = view * model;
        matrix4 mvp = proj * mv;

        vector3 screenVertex[8];
        vector3 viewVertex[8];//旋转未透视点直角坐标

        for (int i = 0;i < 8;i++)
        {
            viewVertex[i] = mv.transformPoint(cubeVertex[i]);
            vector3 temp = mvp.transformPoint(cubeVertex[i]);
            float cw = mvp.get_m(3, 0) * cubeVertex[i].get_xyz('x') + mvp.get_m(3, 1) * cubeVertex[i].get_xyz('y') +
                mvp.get_m(3, 2) * cubeVertex[i].get_xyz('z') + mvp.get_m(3, 3);

            float ndc_x = temp.get_xyz('x') / cw;
            float ndc_y = temp.get_xyz('y') / cw;
            float ndc_z = temp.get_xyz('z') / cw;

            screenVertex[i].set((ndc_x + 1) * 0.5f * w, (1 - ndc_y) * 0.5f * h, (ndc_z + 1) * 0.5);
        }


        // 每个面两个三角形，共 12 个三角形
        // 每个三角形的三个顶点 UV
        //（0，0）顺时针依次对应7546
        float faceUV[12][3][2] =
        {
            // 前面
            {{1,1},{1,0},{0,1}}, {{1,0},{0,0},{0,1}},
            // 后面 (你实测)
            {{1,1},{1,0},{0,1}}, {{1,0},{0,0},{0,1}},
            // 底面
            {{1,1},{1,0},{0,1}}, {{1,0},{0,0},{0,1}},
            // 顶面
            {{1,1},{1,0},{0,1}}, {{1,0},{0,0},{0,1}},
            // 左面
            {{1,1},{1,0},{0,1}}, {{1,0},{0,0},{0,1}},
            // 右面
            {{1,1},{1,0},{0,1}}, {{1,0},{0,0},{0,1}}
        };

        for (int i = 0; i < 12; i++) {
            // 计算法线
            vector3 AB = viewVertex[cubeface[i][1]] - viewVertex[cubeface[i][0]];
            vector3 AC = viewVertex[cubeface[i][2]] - viewVertex[cubeface[i][0]];
            vector3 n = AC.cross(AB).normalized();

            // 获取当前三角形的 UV
            float u0 = faceUV[i][0][0], v0 = faceUV[i][0][1];
            float u1 = faceUV[i][1][0], v1 = faceUV[i][1][1];
            float u2 = faceUV[i][2][0], v2 = faceUV[i][2][1];

            Triangle tri(
                screenVertex[cubeface[i][0]], screenVertex[cubeface[i][1]], screenVertex[cubeface[i][2]],
                cubeColors[i], cubeColors[i], cubeColors[i], n,
                u0, v0, u1, v1, u2,v2,
                &tex);
            bool opentex = true;//纹理开关
            if(opentex)tri.disableTexture();//纹理关闭
            tri.draw_Triangle(fb, proj);
            
        }

        // 用方向键控制旋转
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  angleY -= anglev;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) angleY += anglev;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    angleX -= anglev;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  angleX += anglev;
        
        // 显示...
        sf::Image image(sf::Vector2u(w, h));
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x)
            {
                Color c = fb.get_pixels(x, y);
                image.setPixel(sf::Vector2u(x, y), sf::Color(c.r, c.g, c.b));
            }
        sf::Texture texture;
        (void)texture.loadFromImage(image);
        sf::Sprite sprite(texture);
        window.draw(sprite);
        window.display();
    }
}
int main()
{
    //内存池测试
    pool_test();
    //智能指针测试
    shared_ptr_test();
    //vector3测试
    vector3_test();
    //matrix4测试
    matrix4_test();
    //bresenham画线算法测试
    draw_line_test();
    //重心填充三角形绘制爱心测试
    draw_Triangle_test();
    //旋转立方体(漫反射高光)测试
    rotating_cube_test();
    
}