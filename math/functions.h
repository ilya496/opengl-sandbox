#pragma once

#include "base.h"

namespace math
{
    inline float toRad(float degrees) 
    { 
        return degrees * (M_PI / 180.0f); 
    }

    inline float toDeg(float radians)
    { 
        return radians * (180.0f / M_PI); 
    }

    template<typename T>
    inline constexpr float dot(T x, T y)
    {
        return x * y;
    }
}