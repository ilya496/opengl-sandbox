#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    struct vec<4, T> {
        typedef vec<4, T> type;
        T x, y, z, w;

        vec() : x(0), y(0), z(0), w(0) {}
        vec(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
        vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        T operator*(const type& other) const
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        friend std::ostream& operator<<(std::ostream& os, const type& vec)
        {
            return os << "vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        }
    };
}