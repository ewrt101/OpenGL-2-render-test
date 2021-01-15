#pragma once

#include "BUILD_ORDER.h"

class Wall_border {
private:
    float length;
    float height;
    float vx[250];
    float vy[250];
    float vz[250];
    float wx[250];
    float wy[250];
    float wz[250];
    void loadTexture();
    GLuint txId;
public:
    Wall_border(float lenght, float height);

    void draw();
};