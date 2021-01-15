#pragma once

#include "Types.h"

class Vector3 {
public:
    float x;
    float y;
    float z;
    Vector3(float _x, float _y, float _z);
    Vector3 operator-(Vector3);
    Vector3 operator+(Vector3);
    Vector3 operator*(float);
};