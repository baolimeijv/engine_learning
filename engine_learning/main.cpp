#include <iostream>
#include <cmath>
#include "vector3.h"
#include "matrix4.h"
#include"shared_ptr.h"
#include"memory_pool.h"
#include "framebuffer.h"
#include "draw_line.h"
#include <SFML/Graphics.hpp>
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

    Framebuffer fb(800, 600);
    Color red(255, 0, 0);
    Color green(0, 255, 0);
    Color blue(0, 0, 255);

    draw_line(fb, 100, 100, 700, 500, red);
    draw_line(fb, 100, 500, 700, 100, green);
    draw_line(fb, 100, 300, 700, 300, blue);

     sf::RenderWindow window(sf::VideoMode({800, 600}), "Line Test");
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