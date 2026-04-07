#pragma once
#include "vector3.h"

class matrix4 {
private:
    float m[4][4];
public:
    matrix4();
    void setIdentity();
    static matrix4 identity();
    static matrix4 translation(float x, float y, float z);
    static matrix4 rotationX(float a);
    static matrix4 rotationY(float a);
    static matrix4 rotationZ(float a);
    static matrix4 scale(float x, float y, float z);
    matrix4 operator*(const matrix4& other) const;
    vector3 transformPoint(const vector3& p) const;
    vector3 transformVector(const vector3& v) const;
};