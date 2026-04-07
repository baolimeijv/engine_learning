#pragma once

#include <iostream>
#include <cmath>

class vector3 {
private:
    float x, y, z;
public:
    friend class matrix4;
    // 构造函数
    vector3(float x = 0, float y = 0, float z = 0);

    // 加减乘除
    vector3 operator+(const vector3& v) const;
    vector3 operator-(const vector3& v) const;
    vector3 operator*(float a) const;
    vector3 operator/(float a) const;
    vector3& operator+=(const vector3& v);
    vector3& operator-=(const vector3& v);

    // 点积、叉积
    float dot(const vector3& v) const;
    vector3 cross(const vector3& v) const;

    // 模长、单位化
    float length() const;
    vector3 normalized() const;

    // 输出流友元
    friend std::ostream& operator<<(std::ostream& os, const vector3& v);
};
