#include "matrix4.h"
#include <cmath>

matrix4::matrix4() {
    setIdentity();
}

void matrix4::setIdentity() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = (i == j) ? 1.0f : 0.0f;
}

matrix4 matrix4::identity() {
    matrix4 mat;
    return mat;
}

matrix4 matrix4::translation(float x, float y, float z) {
    matrix4 mat;
    mat.m[0][3] = x;
    mat.m[1][3] = y;
    mat.m[2][3] = z;
    return mat;
}

matrix4 matrix4::rotationX(float a) {
    matrix4 mat;
    float c = cos(a), s = sin(a);
    mat.m[1][1] = c;
    mat.m[2][2] = c;
    mat.m[1][2] = -s;
    mat.m[2][1] = s;
    return mat;
}

matrix4 matrix4::rotationY(float a) {
    matrix4 mat;
    float c = cos(a), s = sin(a);
    mat.m[0][0] = c;
    mat.m[2][2] = c;
    mat.m[0][2] = s;
    mat.m[2][0] = -s;
    return mat;
}

matrix4 matrix4::rotationZ(float a) {
    matrix4 mat;
    float c = cos(a), s = sin(a);
    mat.m[0][0] = c;
    mat.m[1][1] = c;
    mat.m[0][1] = -s;
    mat.m[1][0] = s;
    return mat;
}

matrix4 matrix4::scale(float x, float y, float z) {
    matrix4 mat;
    mat.m[0][0] = x;
    mat.m[1][1] = y;
    mat.m[2][2] = z;
    return mat;
}

matrix4 matrix4::operator*(const matrix4& other) const {
    matrix4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

matrix4 matrix4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
    matrix4 mat;
    mat.m[0][0] = 2.0f / (right - left);
    mat.m[1][1] = 2.0f / (top - bottom);
    mat.m[2][2] = -2.0f / (far - near);
    mat.m[0][3] = -(right + left) / (right - left);
    mat.m[1][3] = -(top + bottom) / (top - bottom);
    mat.m[2][3] = -(far + near) / (far - near);
    return mat;
}

matrix4 matrix4::perspective(float fov, float aspect, float near, float far) 
{
    matrix4 mat;
    float tanHalfFov = tan(fov / 2.0f);
    mat.m[0][0] = 1.0f / (aspect * tanHalfFov);
    mat.m[1][1] = 1.0f / tanHalfFov;
    mat.m[2][2] = -(far + near) / (far - near);
    mat.m[2][3] = -(2.0f * far * near) / (far - near);
    mat.m[3][2] = -1.0f;
    mat.m[3][3] = 0.0f;
    return mat;
}

vector3 matrix4::transformPoint(const vector3& p) const {
    float x = m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3];
    float y = m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3];
    float z = m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3];
    return vector3(x, y, z);
}

vector3 matrix4::transformVector(const vector3& v) const {
    float x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
    float y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
    float z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
    return vector3(x, y, z);
}
//计算行列式
float matrix4:: det() const
{
    return m[0][0] * m[1][1] * m[2][2] + m[0][2] * m[1][0] * m[2][1] + m[2][0] * m[0][1] * m[1][2]
        - m[0][2] * m[1][1] * m[2][1] - m[0][0] * m[2][1] * m[1][2] - m[2][2] * m[1][0] * m[0][1];
}

float matrix4::get_m(int x,int y) const
{
    return m[x][y];
}
