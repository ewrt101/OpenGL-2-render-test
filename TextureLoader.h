#pragma once

#include "BUILD_ORDER.h"


class TextrueLoader_TGA {
private:
    const char* fname;
public:
    GLuint txId;
    TextrueLoader_TGA(const char* fname);
    void loadTexture();
};

class TextrueLoader_BMP {
private:
    const char* fname;
public:
    GLuint txId;
    TextrueLoader_BMP(const char* fname);
    void loadTexture();
};
