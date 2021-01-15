#pragma once

#include "BUILD_ORDER.h"

class Plane {
private:
    float base_size;
    float tile_size;
    Color* base_color;
    Color* tile_color;
public:
    Plane(float size, float tile, Color color1, Color color2);

    void draw();
};