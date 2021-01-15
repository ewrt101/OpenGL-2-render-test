#include "Color.h"

Color::Color(float _r, float _g, float _b){
    r = _r;
    g = _g;
    b = _b;
    a = 1;
}

Color::Color(float _r, float _g, float _b, float _a){
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}