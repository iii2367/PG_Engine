#ifndef GFXMATH_H
#define GFXMATH_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

using Vec2 = glm::vec2;
using Vec4 = glm::vec4;

struct Rect
{
    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;
};

struct Color
{
    float r = 1;
    float g = 1;
    float b = 1;
    float a = 1;
};

#endif
