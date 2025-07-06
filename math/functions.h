#pragma once

#include "base.h"

namespace math
{
    inline float toRad(float degrees)
    {
        return degrees * (static_cast<float>(M_PI) / 180.0f);
    }

    inline float toDeg(float radians)
    {
        return radians * (180.0f / static_cast<float>(M_PI));
    }

    template<typename T>
    inline float length(const T& v)
    {
        return sqrt(dot(v, v));
    }

    template<typename T>
    inline constexpr float dot(T x, T y)
    {
        return x * y;
    }

    template<typename T>
    T normalize(const T& v)
    {
        if (dot(v, v) == 0) return T(0);
        return v * (1 / sqrt(dot(v, v)));
    }

    template<typename T>
    vec<3, T> cross(const vec<3, T>& v1, const vec<3, T>& v2)
    {
        return vec<3, T>(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        );
    }
}