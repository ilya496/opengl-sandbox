#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    struct vec<3, T> {
        typedef vec<3, T> type;
        T x, y, z;

        vec() : x(0), y(0), z(0) {}
        vec(T scalar) : x(scalar), y(scalar), z(scalar) {}
        vec(T x, T y, T z) : x(x), y(y), z(z) {}

        friend std::ostream& operator<<(std::ostream& os, const type& vec)
        {
            return os << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        }
    };
}