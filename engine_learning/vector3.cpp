#include "vector3.h"

// 构造函数
vector3::vector3(float x, float y, float z) : x(x), y(y), z(z) {}

// 加法
vector3 vector3::operator+(const vector3& v) const {
    return vector3(x + v.x, y + v.y, z + v.z);
}

// 减法
vector3 vector3::operator-(const vector3& v) const {
    return vector3(x - v.x, y - v.y, z - v.z);
}

// 数乘（向量 * 标量）
vector3 vector3::operator*(float a) const {
    return vector3(a * x, a * y, a * z);
}

// 数除（向量 / 标量）
vector3 vector3::operator/(float a) const {
    return vector3(x / a, y / a, z / a);
}

// 复合加法
vector3& vector3::operator+=(const vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

// 复合减法
vector3& vector3::operator-=(const vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

// 点积
float vector3::dot(const vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// 叉积
vector3 vector3::cross(const vector3& v) const {
    return vector3(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

// 模长
float vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// 单位化
vector3 vector3::normalized() const {
    float len = length();
    if (len == 0) return *this;
    return *this / len;
}

// 输出流
std::ostream& operator<<(std::ostream& os, const vector3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}